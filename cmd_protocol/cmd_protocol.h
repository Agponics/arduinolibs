// Author: Brian Scully
// Copyright (c) 2016 Agponics

#ifndef __CMD_PROTOCOL_H__
#define __CMD_PROTOCOL_H__

#include <Arduino.h>

#define SERIAL_BAUD 9600     // baud rate for serial transmission (must match up w/ the other side)
#define READ_DELAY       100 // delay between checks for input from the serial connection 

#ifndef DBGMSG
#define DBGMSG(msg)
#endif

#define CMD_DBG 0 // turn on to get detailed debug info for this module

#if CMD_DBG == 1
#define CMD_PROTOCOL_DBGMSG(msg) DBGMSG(msg); 
#else 
#define CMD_PROTOCOL_DBGMSG(msg)
#endif

typedef enum eCmdType
{
    INVALID = 0, // invalid command type (for defaults)
    SET = 1,     // enable or disable a relay switch
    GET = 2,     // get information about all devices attached to the arduino
} CmdType;


// blocking call, returns true for success, false for failure
boolean read_command(String& cmd);

// parses a simple command string from the serial port
// GET: the caller wants a detailed status reported from the arduino for all attached devices and sensors
// SET:[index]:[enable (0 or 1)]: the caller wants the arduino to enable or disable a relay switch 

unsigned int parse_command(String cmd, unsigned int& switch_index, boolean& enable);

#endif // __CMD_PROTOCOL_H__

