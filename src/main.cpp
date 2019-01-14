
#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Robot.hpp"
#include "Commands.hpp"
#include "Fileio.hpp"


std::vector<int> parseInputArray(std::string inputString){
    std::vector<int> input;
    std::string tmpString;
    int tmpNumber;
    
    for(int i = 0; i< inputString.size(); i++){
        char c = inputString[i];
        if(c >= '0' && c <= '9'){
            tmpString.push_back(c);
        }else if(c == ','){
           
            std::istringstream iss(tmpString);
            iss >> tmpNumber;
            tmpString.clear();
            input.push_back(tmpNumber);
        }
    }
    
    std::istringstream iss(tmpString);
    iss >> tmpNumber;
    input.push_back(tmpNumber);

    return input;
}

int main(int argc, char const *argv[]) {
    
    std::string inputString;
    std::vector<int> input; //= {1, 2, 3};

    if(argc == 3){
        Fileio file(argv[1]);
        inputString = file.getFileContent();
        input = parseInputArray(argv[2]);
    }else{
        std::cout << "Usage: robot <filename> <input array>" << std::endl;
        exit(1);
    }
    
    Parser parser(inputString);
    std::map<std::string, std::vector<Command>> commands = parser.getPlaces();
    
    Robot robot(input, commands);
    robot.runProgram();

    return 0;
}
