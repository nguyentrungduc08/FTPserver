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
    this->currentOpentReadFile.open(fileName.c_str(), std::ios::in|std::ios::binary);

    if (this->currentOpentReadFile.fail()){
    	std::cerr << "Reading file " << fileName << "failed!" << std::endl;
    	return (EXIT_FAILURE);
    }
    if  (this->currentOpentReadFile.is_open()) {
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

void filehandle::getValidDir(std::string& dirName){
    std::string slash = "/";
    size_t  foundSlash = 0;
    while ( (foundSlash = dirName.find_first_of(slash),(foundSlash)) != std::string::npos ){
        dirName.erase(foundSlash++,1);
    } 
    dirName.append(slash);
}

void filehandle::getValidFile(std::string& fileName){
    std::string slash = "/";
    size_t foundSlash = 0;
    while ( (foundSlash = fileName.find_first_of(slash), (foundSlash)) != std::string::npos ){
        fileName.erase(foundSlash++,1);
    }
}

//read data from file
char * filehandle::readFileBlock(unsigned long& sizeInBytes){
    //get length of file
    this->currentOpentReadFile.seekg(0, std::ios::end);
    std::ifstream::pos_type size = this->currentOpentReadFile.tellg();
    sizeInBytes = (unsigned long) size;
    
    this->currentOpentReadFile.seekg(0, std::ios::beg);
    
    //allocate memory
    char * memblock = new char[size];
    
    //read data and save to memblock
    this->currentOpentReadFile.read(memblock, size);
    
    //relese memory of block 
    std::cout <<"Reading " << size << " Bytes" << std::endl;
    this->currentOpentReadFile.close();
    return memblock;    
}