#ifndef __TURING_COMMANDS_H
#define __TURING_COMMANDS_H

#include <iostream>

enum commandType{
    INPUT_COMMAND,
    OUTPUT_COMMAND,
    
    ADD_COMMAND,
    SUB_COMMAND,
    
    COPYTO_COMMAND,
    COPYFROM_COMMAND,
    
    JUMP_COMMAND,
    JUMPIFNEG_COMMAND,
    JUMPIFZERO_COMMAND
};

struct Command{
    commandType type;

    int position;
    std::string placeName;
};


#endif
