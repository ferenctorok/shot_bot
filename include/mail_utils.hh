#pragma once

#include <Arduino.h>
#include <ESP_Mail_Client.h>
#include <vector>

#include "globals.hh"


/// @brief Enum class for representing success or failure of a process.
enum class SuccessCode
{
    success = 0,
    failure = 1
};


/// @brief Tries to connect to a wifi network.
/// @param[in] ssid The SSID of the network.
/// @param[in] password The password to the network.
/// @param[in] max_wait_time The maximum amount of time to try to connect.
/// @return Returns a SuccessCode about the success of the connection.
const SuccessCode connect_to_wifi_single(
    const String ssid, const String password, const float max_wait_time = 10.0f);

/// @brief Connects to one of the wifis listed in the vector of wifi_credentials.
/// @param wifi_credentials Vector of wifi credentials to try to connect to.
/// @param max_wait_time The maximum amount of time to try to connect.
/// @param num_tries The number of times to try the whole process.
/// @return 
const SuccessCode connect_to_wifi(std::vector<WifiCredential> wifi_credentials,
    const float max_wait_time = 10.0f, const size_t num_tries = 3UL);


/// @brief Manager class for providing email related functionality.
class GmailManager
{
public:

/// @brief SMTP session that is used by all instances of this class.
static SMTPSession smtp;

/// @brief Sets up the SMTP server for a given email address and password.
/// @param sender_address The complete email address of the form name@gmail.com
/// @param sender_password App password for the gmail account.
GmailManager(const String sender_address, const String sender_password, const String sender_name);
GmailManager(const GmailManager&) = delete;
GmailManager(GmailManager&&) = delete;
GmailManager& operator=(const GmailManager&) = delete;
GmailManager& operator=(GmailManager&&) = delete;

/// @brief Callback function to get the Email sending status.
/// @param status The status received from the smtp object.
static void smtpCallback(SMTP_Status status);

/// @brief Sends out an email to the recipient with the given subject and content.
/// @param recipient_address The recipient to send the mail to.
/// @param subject The subject of the email.
/// @param text The content of the email.
/// @return Returns a SuccessCode about the success of sending the email.
const SuccessCode send_mail(
    const String recipient_address, const String subject, const String text);

/// @brief ESP mail session of this sender.
ESP_Mail_Session session;

private:

String sender_address;
String sender_password;
String sender_name;
};
