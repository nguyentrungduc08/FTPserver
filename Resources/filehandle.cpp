/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filehandle.cpp
 * Author: nguyen trung duc
 * 
 * Created on December 5, 2017, 6:22 PM
 */

#include "../Header/filehandle.h"

filehandle::filehandle(std::string dir) {
    this->completePath.push_front(dir);
}

filehandle::filehandle(const filehandle& orig) {
}

filehandle::~filehandle() {
    this->completePath.clear();
}
int filehandle::readFile(std::string fileName){
    stripServerRootString(fileName);
    //set binary file model
    this->currentOpenReadFile.open(fileName.c_str(), std::ios::in|std::ios::binary);

    if (this->currentOpenReadFile.fail()){
    	std::cerr << "Reading file " << fileName << "failed!" << std::endl;
    	return (EXIT_FAILURE);
    }
    f (this->currentOpenReadFile.is_open()) {
        return (EXIT_SUCCESS);
    }
    std::cerr << "Unable to open file '" << fileName << " '" << std::endl; // << strerror(errno)
    return (EXIT_FAILURE);
}


void filehandle::stripServerRootString(std::string &dirOrFileName){
    size_t foundRootString = 0;
    if ( ( dirOrFileName.find_first_of(SERVERROOTPATHSTRING) ) == foundRootString ){
        int rootStringLength = ( (std::string) SERVERROOTPATHSTRING).length();
        dirOrFileName = dirOrFileName.substr( rootStringLength, dirOrFileName.length() - rootStringLength);
    }
}
