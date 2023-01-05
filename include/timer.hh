#pragma once

#include "Arduino.h"


/// @brief Timer class for randomly setting an alarm between a minimum and maximum time.
class Timer
{
public:
    /// @brief Only constructor available. Constructs a timer object.
    /// @param min_time_min The minimum time in minutes before which the timer should never go off.
    /// @param max_time_min  The maximum time in minutes until which the timer should go off.
    Timer(const uint8_t min_time_min, const uint8_t max_time_min) noexcept;

    /// @brief Other constructors and assignment operators are deleted here explicitely.
    Timer() = delete;
    Timer(const Timer& other) = delete;
    Timer(Timer&& other) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer& operator=(Timer&&) = delete;

    /// @brief Checks whether the alarm has gone off.
    /// @return True, if the alarm has gone off.
    [[nodiscard]] bool has_timer_went_off() const;

private:
    /// @brief The time in milliseconds when the alarm will go off.
    uint32_t random_alarm_time_ms;
};
