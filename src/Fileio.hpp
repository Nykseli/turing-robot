#ifndef __TURING_FILEIO_H
#define __TURING_FILEIO_H

#include <iostream>

class Fileio {
    
    public:
        Fileio(const char* fileName);
        std::string getFileContent();
        
    private:
       const char* fileName;
    
};

#endif
