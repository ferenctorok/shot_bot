#pragma once

#include "Arduino.h"
#include "io_base.hh"


/// @brief Class for containing the buzzer functionality. Inherits from the IOBase base class.
class Buzzer : public IOBase
{
public:
    /// @brief Does a cycle of buzzer noise.
    void do_a_cycle() const;

    /// @brief Shuts the buzzer off.
    void quiet() const;
};
