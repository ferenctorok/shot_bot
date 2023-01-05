#pragma once

#include "Arduino.h"

#include "io_base.hh"


/// @brief Class for containing the Led functionality.
class Led : public IOBase
{
public:
    /// @brief Turns on the led.
    void turn_on() const;

    /// @brief Turns off the led.
    void turn_off() const;
};
