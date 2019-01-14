
#include <iostream>
#include <fstream>
#include <string>

#include "Fileio.hpp"

Fileio::Fileio(const char* fileName){
    this->fileName = fileName;
}

std::string Fileio::getFileContent(){
    std::string fileContent;
    std::string tmpLine;
    std::ifstream programFile(this->fileName);
    if(programFile.is_open()){
        while(getline(programFile, tmpLine)){
            fileContent += tmpLine;
            fileContent.push_back('\n');
        }
        programFile.close();
    }else{
        std::cout << "No file found: " << this->fileName << std::endl;
    }
    
    return fileContent;
}