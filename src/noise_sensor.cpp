#include "noise_sensor.hh"

#include "Arduino.h"


float NoiseSensor::measure_duty_cycle(const size_t duration_ms) const
{
    size_t high_duration_us{0UL};
    const size_t time0_ms{millis()};
    size_t time1_ms = time0_ms;

    while((time1_ms - time0_ms) < duration_ms)
    {
    const size_t max_timeout_us = (duration_ms - (time1_ms - time0_ms)) * 1000UL;
    high_duration_us += pulseIn(pin, LOW, max_timeout_us);
    time1_ms = millis();
    }

    const float high_duration_ms{static_cast<float>(high_duration_us) / 1000.0f};
    return high_duration_ms / static_cast<float>(duration_ms);
}
