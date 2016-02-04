// Author: Brian Scully
// Copyright (c) 2016 Agponics

#include <cmd_protocol.h>

boolean read_command(String& cmd)
{
    String line = "";

    // wait until there's data available on the serial connection
    while (Serial.available() <= 0)
    {
        delay(READ_DELAY);
    }

    // grab all available bytes from the serial connection and convert to a string:
    while (Serial.available() != 0)
    {
        line += String((char)Serial.read());
        delay(10); // without this slight delay sometimes command strings were cut off
    }

    CMD_PROTOCOL_DBGMSG((String("Received: ") + line))

    cmd = line;
    return true;
}

unsigned int parse_command(String cmd, unsigned int& switch_index, boolean& enable)
{
    CmdType op_type = INVALID;

    cmd.toLowerCase();
    
    if (cmd.startsWith("get"))
    {
        op_type = GET;
    }
    else if (cmd.startsWith("set"))
    {
        // SET commands should be formatted as set:[index]:[enable (0 or 1)]
      
        int index1 = -1;   // index within the command of the first ':'
        int index2 = -1;   // index within the command of the second ':'
        String str_idx;    // the desired pump to control (as a string)
        String str_enable; // whether to enable/disable the pump (as a string)
        int switch_idx = 0;  // the converted index (from string to int)
        
        do
        {
            // find first ':'
            index1 = cmd.indexOf(':');
            if (index1 == -1)
            {
                CMD_PROTOCOL_DBGMSG("SET command given with no parameters") 
                break;
            }
            
            // find second ':'
            index2 = cmd.indexOf(':', index1 + 1);
            if ((index2 <= index1 + 1) ||     // failed to find another ':', or it immediately followed the first
                (index2 >= cmd.length() - 1)) // or there was nothing after it
            {
                CMD_PROTOCOL_DBGMSG("SET command requires a 2nd parameter") 
                break;
            }
            
            // switch index is after the first ':'
            str_idx = cmd.substring(index1 + 1, index2);
            //CMD_PROTOCOL_DBGMSG( (String("switch index as a string: ") + str_idx) ) 
            
            // enable/disable parameter is after the second ':'
            str_enable = cmd.substring(index2 + 1); 
            //CMD_PROTOCOL_DBGMSG( (String("enable/disable as a string: ") + str_enable) ) 
            
            // convert strings to integers
            switch_idx = str_idx.toInt();
            
            // set output parameters
            switch_index = switch_idx;
            enable = (str_enable.toInt() != 0);
            
            op_type = SET;
            
        } while(0);
    }
    else
    {
        // invalid
        DBGMSG("invalid command string")
    }

    return op_type;
}

