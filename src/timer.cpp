#include "timer.hh"


Timer::Timer(const uint8_t min_time_min, const uint8_t max_time_min)
{
    random_alarm_time_ms = random(min_time_min, max_time_min + 1U) * 60U * 1000U;
}

bool Timer::has_timer_went_off() const
{
    return millis() > random_alarm_time_ms;
}
