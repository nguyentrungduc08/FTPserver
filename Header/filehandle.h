/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filehandle.h
 * Author: nguyen trung duc
 *
 * Created on December 5, 2017, 6:22 PM
 */

#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include "FTPs.h"

#define BUFFER_SIZE 4096

class filehandle {
    
public:
    
    filehandle();
    filehandle(const filehandle& orig);
    virtual ~filehandle();

private:
    std::vector<std::string> deletedDirectories;
    std::vector<std::string> deletedFiles;
    void getValidFile(std::string *dirName);

};

#endif /* FILEHANDLE_H */

