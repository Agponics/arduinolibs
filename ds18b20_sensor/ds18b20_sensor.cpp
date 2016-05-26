// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include "ds18b20_sensor.h"

void CDs18b20Sensor::set_pin(int pin) 
{
    CDevice::set_pin(pin); 

    m_one_wire = OneWire(pin); 
    m_dt       = DallasTemperature(&m_one_wire);

    m_dt.begin();
}

String CDs18b20Sensor::get_status_str()
{
    double temp = 0.0;
    
    String out = CDevice::get_status_str();

    // TODO
            
    return out;   
}

String CDs18b20Sensor::get_addrs()
{
    uint8_t next_addr[8] = {0};
    uint8_t i = 0;

    String out = "One-wire Addresses Found:\n";
    
    while (m_dt.getAddress(next_addr, i))
    {
        out += String(i) + ":";
        for (int j = 0; j < 8; j++)
        {
            out += " 0x" + String(next_addr[j], HEX);
        }
        out += "\n";
        i++;
    }

    return out;
}


