// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include "hcsr04_sensor.h"

void CHcsr04Sensor::set_pin(int pin) 
{
    CDevice::set_pin(pin); 

    pinMode(pin, INPUT);
    pinMode(pin+1, OUTPUT); // we assume the trigger pin always immediately follows the echo pin
}

String CHcsr04Sensor::get_status_str()
{
    float duration = 0.0;
    String out = CDevice::get_status_str() + ":";

    HCSR04_DBGMSG("Pulsing Trigger: pin " + String(get_trigger_pin()))

    digitalWrite(get_trigger_pin(), LOW); // make sure the signal is cleared to begin with
    delayMicroseconds(2);
    digitalWrite(get_trigger_pin(), HIGH); // pulse the trigger high for 10 microseconds
    delayMicroseconds(10);
    digitalWrite(get_trigger_pin(), LOW); 

    duration = pulseIn(get_echo_pin(), HIGH);

    HCSR04_DBGMSG("Received duration: " + String(int(duration)))
    
    // since this doesn't need to be super accurate just use the standard 74 microseconds per inch
    // for the speed of sound
    out += String(int(duration / 74 / 2));
            
    return out;   
}