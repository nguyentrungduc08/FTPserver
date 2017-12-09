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

int filehandle::readFile(std::string fileName){
    stripServerRootString(fileName);
    this->currentOpentReadFile.open(fileName.c_str(), std::ios::in|std::ios::binary);
    if (this->currentOpentReadFile.fail()){
        std::cout << "Reading file " << fileName << std::endl;
        return (EXIT_FAILURE);
    }
    
    if (this->currentOpentReadFile.is_open()){
        return (EXIT_SUCCESS);
    }
    
    std::cerr << "Unable to open file " << fileName << std::endl;
    return (EXIT_FAILURE);        
}

int filehandle::writeFileBlock(std::string content){
    if (!this->currentOpentFile){
        std::cerr << "Cannot write to output file " << std::endl;
        return (EXIT_FAILURE);
    }
    
    std::cout <<"Appending to file" << std::endl;
    (this->currentOpentFile) << content;
    return (EXIT_SUCCESS);
}

//close stream file output (write file)
int filehandle::closeWriteFile(){
    if (this->currentOpentFile.is_open()){
        std::cout << "Closing open file " << std::endl;
        this->currentOpentFile.close();
    }
}

int filehandle::writeFileAtOnce(std::string fileName, char* content){
    stripServerRootString(fileName);
    std::ofstream myFile(fileName.c_str(), std::ios::out|std::ios::binary);
    
    if (!myFile){
        std::cerr << "Cannot open output file " << fileName << std::endl;
        return (EXIT_FAILURE);
    }
    myFile << content;
    myFile.close();
    return (EXIT_SUCCESS);
}

bool filehandle::createFile(std::string& fileName, bool strict){
    if (strict){
        this->getValidFile(fileName);
    }
    try{
        std::ofstream fileout;
        fileout.open(this->getCurrentWorkingDir().append(fileName).c_str(), std::ios::out|std::ios::binary|std::ios::app);
        fileout.close();
    } catch (std::exception e){
        std::cerr << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

std::string filehandle::getCurrentWorkingDir(bool showRootPath){
    std::string fullpath = "";
    std::list<std::string>::iterator singleDir;
    for( singleDir = this->completePath.begin(); singleDir != this->completePath.end(); ++singleDir ) {
        if (singleDir == this->completePath.begin()) {
            if (!showRootPath){
                fullpath.append(SERVERROOTPATHSTRING);
            } else{
                //...
            }
        } else{
            fullpath.append(*(singleDir));
        }
    }
}