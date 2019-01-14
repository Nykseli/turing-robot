
#include <sstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "Parser.hpp"

Parser::Parser(std::string input){
    Parser::parseToMap(input);
}

std::map<std::string, std::vector<Command>> Parser::getPlaces(){
    return this->places;
}

std::string Parser::removeWhiteSpace(std::string input){
    std::string output;

    for(int i = 0; i < input.length(); i++){
        if(input[i] != ' ' && input[i] != '\t'){
            output.push_back(input[i]);
        }
    }

    return output;
}

std::vector<std::string> Parser::inputToVector(std::string input){
    std::vector<std::string> inputLines;
    std::istringstream inputStream;
    inputStream.str(input);

    for(std::string line; std::getline(inputStream, line); ){
        inputLines.push_back(this->removeWhiteSpace(line));
    }
    return inputLines;
}

Command Parser::parseOutputCommand(std::string commandString){
    Command command;
    command.type = OUTPUT_COMMAND;
    return command;
}

Command Parser::parseInputCommand(std::string commandString){
    Command command;
    command.type = INPUT_COMMAND;
    return command;
}

int Parser::parseInt(std::string commandString){
    std::string valueString = "";
    int number;
    
    
    for(int i = 0; i < commandString.length(); i++){
        if(commandString[i] == '('){
            i++;
            while(commandString[i] != ')' && i < commandString.length()){
                valueString.push_back(commandString[i]);
                i++;
            }
        }
    }

    if(valueString != ""){
        std::istringstream iss(valueString);
        iss >> number;
    }else{
        //TODO: error and exit
    }
    
    return number;
}

Command Parser::parseAddCommand(std::string commandString){
    Command command;
    command.type = ADD_COMMAND;
    command.position = this->parseInt(commandString);
    
    return command;
}

Command Parser::parseSubCommand(std::string commandString) {
    Command command;
    command.type = SUB_COMMAND;
    command.position = this->parseInt(commandString);
    
    return command;
}


Command Parser::parseCopytoCommand(std::string commandString){
    Command command;
    command.type = COPYTO_COMMAND;
    command.position = this->parseInt(commandString);

    return command;
}

Command Parser::parseCopyfromCommand(std::string commandString){
    Command command;
    command.type = COPYFROM_COMMAND;
    command.position = this->parseInt(commandString);


    return command;
}

std::string Parser::parseString(std::string commandString){
    std::string valueString = "";    
    
    for(int i = 0; i < commandString.length(); i++){
        if(commandString[i] == '('){
            i++;
            while(commandString[i] != ')' && i < commandString.length()){
                valueString.push_back(commandString[i]);
                i++;
            }
        }
    }
    return valueString;
}

Command Parser::parseJumpCommand(std::string commandString){
    Command command;
    command.type = JUMP_COMMAND;
    command.placeName = this->parseString(commandString);
    
    return command;
}

Command Parser::parseJumpifnegCommand(std::string commandString) {
    Command command;
    command.type = JUMPIFNEG_COMMAND;
    command.placeName = this->parseString(commandString);
    
    return command;
}


Command Parser::parseJumpifzeroCommand(std::string commandString){
    Command command;
    command.type = JUMPIFZERO_COMMAND;
    command.placeName = this->parseString(commandString);
    
    return command;
}

Command Parser::parseCommand(std::string commandString){
    if(commandString == "INPUT"){
        return this->parseInputCommand(commandString);
    }else if(commandString == "OUTPUT"){
        return this->parseOutputCommand(commandString);
   }else if(commandString.substr(0, 3) == "ADD"){
        return this->parseAddCommand(commandString);
    }else if(commandString.substr(0, 3) == "SUB"){
        return this->parseSubCommand(commandString);
    }else if(commandString.substr(0, 6) == "COPYTO"){
        return this->parseCopytoCommand(commandString);
    }else if(commandString.substr(0, 8) == "COPYFROM"){
        return this->parseCopyfromCommand(commandString);
    }else if(commandString.substr(0, 4) == "JUMP"){
        return this->parseJumpCommand(commandString);
    }else if(commandString.substr(0, 10) == "JUMPIFZERO"){
        return this->parseJumpifzeroCommand(commandString);
    }else if(commandString.substr(0, 9) == "JUMPIFNEG"){
        return this->parseJumpifnegCommand(commandString);
    }else{
        // TODO: error not found and exit
        std::cout << "Command not found: " + commandString << std::endl;
    }
   
}

void Parser::parseToMap(std::string input){
    std::vector<std::string> inputLines = inputToVector(input);
    std::string place = "";
    std::vector<Command> commands;

    for(std::string const& line: inputLines){
       // If last character is : it defines places name
       if(line[line.length() -1] == ':'){
           // Insert commands to map when new place is found
           if(place != ""){

               place = place.substr(0,  place.length()-1);
               std::cout << place << std::endl;
               this->places.insert(std::pair<std::string, std::vector<Command>>(place, commands));
           }
           place = line;
           commands.clear();
       }else{
           commands.push_back(this->parseCommand(line));
       }

    }

    // After for loop. Insert the last place to map
     if(place != ""){
        // Remove :
        place = place.substr(0,  place.length()-1);
        this->places.insert(std::pair<std::string, std::vector<Command>>(place, commands));
    }

}

