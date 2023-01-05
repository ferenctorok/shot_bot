#include "led.hh"

#include "Arduino.h"


void Led::turn_on() const
{
    digitalWrite(pin, HIGH);
    return;
}

void Led::turn_off() const
{
    digitalWrite(pin, LOW);
    return;
}
