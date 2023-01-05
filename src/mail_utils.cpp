#include "mail_utils.hh"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>


const SuccessCode connect_to_wifi_single(
    const String ssid, const String password, const float max_wait_time)
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");

    float wait_time_s{0.0f};
    constexpr uint16_t delay_ms{1000U};

    while ((WiFi.status() != WL_CONNECTED) && (wait_time_s < max_wait_time))
    {
        delay(delay_ms);
        wait_time_s += (delay_ms / 1000.0f);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.disconnect();
        return SuccessCode::failure;
    }

    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());

    return SuccessCode::success;
}

const SuccessCode connect_to_wifi(std::vector<WifiCredential> wifi_credentials,
    const float max_wait_time, const size_t num_tries)
{
    SuccessCode success_code{SuccessCode::failure};

    for (size_t i{0UL}; i < num_tries; ++i)
    {
        for (const auto& credential : wifi_credentials)
        {
            success_code = connect_to_wifi_single(credential.ssid, credential.password, max_wait_time);
            if (success_code == SuccessCode::success)
            {
                return success_code;
            }
        }
    }

    return success_code;
}

// Initializing the SMTP session.
SMTPSession GmailManager::smtp = SMTPSession();

GmailManager::GmailManager(
    const String sender_address, const String sender_password, const String sender_name) :
    sender_address(sender_address), sender_password(sender_password), sender_name(sender_name)
{
    // Enable debug via Serial port.
    smtp.debug(1);

    // Set the callback function to get the sending results.
    smtp.callback(GmailManager::smtpCallback);

    // Set up the session.
    session.server.host_name = "smtp.gmail.com";
    session.server.port = 465;
    session.login.email = sender_address;
    session.login.password = sender_password;
    session.login.user_domain = "";
}

const SuccessCode GmailManager::send_mail(
    const String recipient_address, const String subject, const String text)
{
    SMTP_Message message;
    message.sender.name = sender_name;
    message.sender.email = sender_address;
    message.subject = subject;
    message.addRecipient("Bela", recipient_address);

    message.text.content = text.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
    message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

    // Connect to server with the session config.
    if (!smtp.connect(&session))
    {
        return SuccessCode::failure;
    }

    // Send Email.
    if (!MailClient.sendMail(&smtp, &message))
    {
        Serial.println("Error sending Email, " + smtp.errorReason());
        return SuccessCode::failure;
    }

    return SuccessCode::success;
}

void GmailManager::smtpCallback(SMTP_Status status)
{
    // Print the current status.
    Serial.println(status.info());

    // Print the sending result.
    if (status.success())
    {
        Serial.println("----------------");
        ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
        ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
        Serial.println("----------------\n");
        struct tm dt;

        for (size_t i = 0; i < smtp.sendingResult.size(); i++)
        {
            SMTP_Result result = smtp.sendingResult.getItem(i);
            time_t ts = (time_t)result.timestamp;
            localtime_r(&ts, &dt);

            ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
            ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
            ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
            ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
            ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
        }

        Serial.println("----------------\n");
    }
}
