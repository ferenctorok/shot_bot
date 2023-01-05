#include <Arduino.h>
#include <optional>

#include "globals.hh"
#include "mail_utils.hh"
#include "timer.hh"
#include "buzzer.hh"
#include "led.hh"
#include "noise_sensor.hh"
#include "mood_detector.hh"


// Initializing the timer.
const Timer timer(MIN_TIME_MIN, MAX_TIME_MIN);

// Email manager.
std::optional<GmailManager> gmail_manager;

// Setting up the IO devices.
Led led{LED_PIN};
Buzzer buzzer{BUZZER_PIN};
NoiseSensor noise_sensor{SENSOR_PIN};

// Setting up the mood detector.
MoodDetector mood_detector{NUM_BASELINE_SAMPLES, NUM_COMPARISON_SAMPLES, SIGNIFICANT_DIFFERENCE};


void setup()
{
  Serial.begin(115200);

  // Setting up pins.
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RANDOM_SEED_PIN, INPUT);

  // Default state for output pins.
  led.turn_off();
  buzzer.quiet();

  // Setting random seed.
  randomSeed(analogRead(RANDOM_SEED_PIN));

  // Trying to connect to the Wifi.
  const auto wifi_success = connect_to_wifi(SSID, WIFI_PASSWORD);

  // Setting up the gmail manager if the wifi connection was successful.
  if (wifi_success == SuccessCode::success)
  {
    gmail_manager.emplace(SENDER_ADDRESS, SENDER_PASSWORD, "Kicsi Bot");
  }

  // Sleeping until shortly before MIN_TIME_MIN. Before that nothing is going to happen.
  delay(MIN_TIME_MIN * 60U * 1000U);
}

void loop()
{
  const float sample{noise_sensor.measure_duty_cycle(SAMPLE_LENGTH_MS)};
  mood_detector.update(sample);
  
  const bool mood_drop_sensed{mood_detector.get_status() == MoodDetector::Status::drop_sensed};
  const bool alarm_went_off{timer.has_timer_went_off()};
  
  if (mood_drop_sensed || alarm_went_off)
  {
    // Send an email if possible.
    if (gmail_manager.has_value())
    {
      gmail_manager->send_mail(RECIPIENT_EMAIL, "Reminder", "KICSI?");
    }

    led.turn_on();

    // Until the devide is not turned off, the buzzer is going to be beeping.
    while (true)
    {
      buzzer.do_a_cycle();
    }
  }
}
