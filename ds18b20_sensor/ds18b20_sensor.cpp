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
    double  temp = 0.0;
    uint8_t probe_cnt = 0;
    
    String out = "";

    // have all probes read temp
    m_dt.requestTemperatures();

    probe_cnt = m_dt.getDeviceCount();

    for (uint8_t i = 0; i < probe_cnt; i++)
    {
        float temp_celsius = m_dt.getTempCByIndex(i);
        out += CDevice::get_status_str();
        out += "probe" + String(i) + ":temp:";
        out += String(int(celsius_to_fahrenheit(temp_celsius)));
        out += "\n";
    }
            
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


