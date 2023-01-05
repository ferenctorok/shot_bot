#pragma once

#include "Arduino.h"


/// @brief implements a simple base class for an IO device operating on a pin.
class IOBase
{
public:
    /// @brief Initializes a IOBase object at the given pin.
    /// @param pin The number of the pin.
    IOBase(const uint8_t pin) noexcept;

    /// @brief Other constructors and assignment operators are deleted here explicitely.
    IOBase() = delete;
    IOBase(const IOBase& other) = delete;
    IOBase(IOBase&& other) = delete;
    IOBase& operator=(const IOBase&) = delete;
    IOBase& operator=(IOBase&&) = delete;

protected:
    /// @brief The pin at which the device is located.
    uint8_t pin;
};
