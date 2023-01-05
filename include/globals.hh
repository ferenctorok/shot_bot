// Header file for containing the global constants used in the program.

#pragma once

#include "Arduino.h"
#include <vector>


// Pins.
constexpr uint8_t LED_PIN{D0};
constexpr uint8_t BUZZER_PIN{D1};
constexpr uint8_t SENSOR_PIN{D2};

// Random seed based on some unconnected pin.
constexpr uint8_t RANDOM_SEED_PIN(D6);

// Wifi connection.
struct WifiCredential
{
    String ssid;
    String password;
};

const std::vector<WifiCredential> WIFI_CREDENTIALS
{
    // WifiCredential{"FRITZ!Box 7530 XF", "04236449658141056366"},
    WifiCredential{"Nagyhaz", "csehtorok61"},
    WifiCredential{"HUAWEI Mate 20 lite", "1234567890"},
    
};

// Email.
const String SENDER_ADDRESS{"kicsi.bot69@gmail.com"};
const String SENDER_PASSWORD{"siomkzblyajbhiyn"};
const String RECIPIENT_EMAIL{"balint.lnd@gmail.com"};

// Timer.
constexpr uint8_t MIN_TIME_MIN{20U};
constexpr uint8_t MAX_TIME_MIN{40U};

// Noise sensor.
constexpr size_t SAMPLE_LENGTH_MS{500UL};

// Mood detector.
constexpr uint8_t NUM_BASELINE_SAMPLES{14U};
constexpr uint8_t NUM_COMPARISON_SAMPLES{8U};
constexpr float SIGNIFICANT_DIFFERENCE{0.15f};
