
#include <iostream>
#include <cstdlib>
#include "Robot.hpp"
#include "Parser.hpp"


Robot::Robot(std::vector<int> input, std::map<std::string, std::vector<Command>> places){
    this->input = input;
    this->places = places;

    this->inputPosition = 0;
    this->hand.empty = true;
}

void Robot::inputCommand(){
    this->hand.value = this->input[this->inputPosition];
    this->hand.empty = false;
    this->inputPosition++;
   
    // exit if current position is last one
    if(this->inputPosition > this->input.size()){
        exit(0);
    }
}

void Robot::outputCommand(){
    if(!this->hand.empty){
        std::cout << this->hand.value << std::endl;
        this->hand.empty = true;
    }else{
        //TODO: error
    }

}

void Robot::addCommand(Command command) {
    int position = command.position;
    if(!this->hand.empty){
        std::map<int, int>::iterator it = this->memory.find(command.position);
        if(it != this->memory.end()){
            this->hand.value += it->second;
        }else{
            // error: no value in memory position
        }
    }else{ 
        // error: hand is empty
    }
}

void Robot::subCommand(Command command) {
    int position = command.position;
    if(!this->hand.empty){
        std::map<int, int>::iterator it = this->memory.find(command.position);
        if(it != this->memory.end()){
            this->hand.value -= it->second;
        }else{
            // error: no value in memory position
        }
    }else{ 
        // error: hand is empty
    }
}

void Robot::copytoCommand(Command command){
    //CopytoCommand* cCommand = (CopytoCommand*) command.command;
    if(!this->hand.empty){
        std::map<int, int>::iterator it = this->memory.find(command.position);
        if(it != this->memory.end()){
            it->second = this->hand.value;
        }else{
            this->memory.insert(std::pair<int, int>(command.position, this->hand.value));
        }
    }else{
        //TODO: error
    }
}

void Robot::copyfromCommand(Command command){
    //CopyfromCommand* cCommand = (CopyfromCommand*) command.command;
    this->hand.value = this->memory.find(command.position)->second;
    this->hand.empty = false;
}

void Robot::jumpCommand(Command command){
    this->iteratePlace(command.placeName);
}

void Robot::jumpifnegCommand(Command command) {
    if(!this-hand.empty){
        if(this->hand.value < 0){
            this->iteratePlace(command.placeName);
        }
    }else{
        // error empty hand
    }
}


void Robot::jumpifzeroCommand(Command command) {
    if(!this-hand.empty){
        if(this->hand.value == 0){
            this->iteratePlace(command.placeName);
        }
    }else{
        // error empty hand
    }
}

void Robot::iteratePlace(std::string placeName){
    std::map<std::string, std::vector<Command>>::iterator it = this->places.find(placeName);
    
    if(it != this->places.end()){
         std::vector<Command> commands = it->second;

        for(auto const &command: commands){
       
            switch(command.type){
                case INPUT_COMMAND:
                    this->inputCommand();
                    break;
                case OUTPUT_COMMAND:
                    this->outputCommand();
                    break;
                case ADD_COMMAND:
                    this->addCommand(command);
                    break;
                case SUB_COMMAND:
                    this->subCommand(command);
                    break;
                case COPYTO_COMMAND:
                    this->copytoCommand(command);
                    break;
                case COPYFROM_COMMAND:
                    this->copyfromCommand(command);
                    break;
                case JUMP_COMMAND:
                    this->jumpCommand(command);
                    break;
                case JUMPIFZERO_COMMAND:
                    this->jumpifzeroCommand(command);
                    break;
                case JUMPIFNEG_COMMAND:
                    this->jumpifnegCommand(command);
                    break;
                default:
                    // Command not found and parser hash failed
                    break;
            }
        }
    }else{
        //error no place found and exit
    }
}

void Robot::runProgram(){
    this->iteratePlace("Start");
}
