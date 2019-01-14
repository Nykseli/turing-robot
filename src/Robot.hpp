#ifndef __TURING_ROBOT_H
#define __TURING_ROBOT_H

#include "Commands.hpp"

#include <vector>
#include <map>

struct robotHand{
    bool empty;
    int value;
};

class Robot {

    public:
        Robot( std::vector<int> input, std::map<std::string, std::vector<Command>> places);
        void runProgram();

    private:
        std::map<int, int> memory;
        std::map<std::string, std::vector<Command>> places;
        std::vector<int> input;
        struct robotHand hand;
        int inputPosition;
        
        void iteratePlace(std::string placeName);
        
        void inputCommand();
        void outputCommand();
        
        void addCommand(Command command);
        void subCommand(Command command);
        
        void copytoCommand(Command command);
        void copyfromCommand(Command command);

        void jumpCommand(Command command);
        void jumpifzeroCommand(Command command);
        void jumpifnegCommand(Command command);
};

#endif
