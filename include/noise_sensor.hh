#pragma once

#include "io_base.hh"


/// @brief Class for containing the NoiseSensor functionality. Inherits from the IOBase base class.
class NoiseSensor : public IOBase
{
public:
    /// @brief Measures the duty cycle of the nonperiodic digital signal that comes from the noise sensor.
    /// @param duration_ms The duration of measurement.
    /// @return the value of the duty cycle.
    [[nodiscard]] float measure_duty_cycle(const size_t duration_ms) const;
};
