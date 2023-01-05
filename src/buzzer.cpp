#include "buzzer.hh"

#include "Arduino.h"


void Buzzer::do_a_cycle() const
{
    for (uint8_t i{0U}; i <  3U; ++i)
    {
        digitalWrite(pin, HIGH);
        delay(125);
        digitalWrite(pin, LOW);
        delay(125);
    }

    delay(1250);
    return;
}

void Buzzer::quiet() const
{
    digitalWrite(pin, LOW);
    return;
}
