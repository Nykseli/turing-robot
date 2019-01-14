#ifndef __TURING_PARCER_H
#define __TURING_PARCER_H

#include <iostream>
#include <vector>
#include <map>

#include "Commands.hpp"

class Parser {

    public:
        Parser(std::string);
        std::map<std::string, std::vector<Command>> getPlaces();

    private:
        std::map<std::string, std::vector<Command>> places;
        std::vector<std::string> inputToVector(std::string);
        std::string removeWhiteSpace(std::string);
        void parseToMap(std::string);
        
        int parseInt(std::string);
        std::string parseString(std::string);
        
        Command parseCommand(std::string);
        
        Command parseInputCommand(std::string);
        Command parseOutputCommand(std::string);
        
        Command parseAddCommand(std::string);
        Command parseSubCommand(std::string);
        
        Command parseCopytoCommand(std::string);
        Command parseCopyfromCommand(std::string);
        
        Command parseJumpifnegCommand(std::string);
        Command parseJumpifzeroCommand(std::string);
        Command parseJumpCommand(std::string);

};

#endif
