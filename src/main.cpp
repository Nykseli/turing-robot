
#include <iostream>
#include "Parser.hpp"
#include "Robot.hpp"
#include "Commands.hpp"

int main(int argc, char const *argv[]) {

    std::vector<int> input = {1, 2, 3};

    std::string inputString = "Start:\nINPUT\nCOPYTO(0)\nSUB(0)\nSUB(0)\nOUTPUT\nJUMPIFNEG(Start)\nCOPYFROM(0)\nADD(0)\nOUTPUT\nJUMP(Start)";

    Parser parser(inputString);
    std::map<std::string, std::vector<Command>> commands = parser.getPlaces();
    
    Robot robot(input, commands);
    robot.runProgram();

    return 0;
}
