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
#define SERVERROOTPATHSTRING "<root>/"

class filehandle {
    
public:
    
    filehandle(std::string dir);
    filehandle(const filehandle& orig);
    virtual ~filehandle();
    
    int readFile(std::string fileName);
    char * readFileBlock(unsigned long &sizeInBytes);
    
    int writeFileAtOnce(std::string fileName, char * content);
    int beginWriteFile(std::string fileName);
    int writeFileBlock(std::string content);
    int closeWriteFile();
    
    bool changeDir(std::string newPath, bool strict = true);
    std::string  getCurrentWorkingDir(bool showRootPath = true);
   
    bool createDirectory(std::string &dirName, bool strict = true);
    bool createFile(std::string &fileName, bool strict = true);
    bool deleteDirectory(std::string dirName, bool cancel = false, std::string pathToDir = "");
    bool deleteFile(std::string fileName, bool strict = true);
    void browse(std::string dir, std::vector<std::string> &directories, std::vector<std::string> &files, bool strict = true);
    
    bool dirCanOpen(std::string dir);
    std::string getParentDir();
    unsigned long getDirSize(std::string dirName);
    std::vector<std::string> getStats (std::string fileName, struct stat Status);
    void clearListOfDeletedFiles();
    void clearListOfDeletedDirectories();
    std::vector<std::string> getDeletedFiles();
    std::vector<std::string> getDeletedDirectories();
    
    bool dirIsBelowServerRoot(std::string dirName);
    
private:
    std::vector<std::string> deletedDirectories;
    std::vector<std::string> deletedFiles;
    
    std::ofstream currentOpentFile;
    std::ifstream currentOpentReadFile;
    
    //the path from server root dir upwards to the current working dir, each list element containing one dir
    std::list<std::string> completePath;
    
    static void IntToString(int i, std::string & res);
    void stripServerRootString(std::string &dirOrFileName);
    void getValidDir(std::string &dirName);
    void getValidFile(std::string &fileName);
    
    
};

#endif /* FILEHANDLE_H */

