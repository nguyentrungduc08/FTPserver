/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nguyen trung duc
 *
 * Created on December 4, 2017, 11:44 AM
 */

#include "Header/FTPs.h"
#include "Header/CoreServer.h"
#include "Header/filehandle.h"
#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    unsigned short commandOffset = 1;
    unsigned int port = 54321;
    std::string dir = "./";
    
    if (argc < 2){
        std::cerr << "Usage: ftpserver <dir> <port> " << std::endl;
    } else {
        switch (argc){
            case 2:{
                filehandle * db = new filehandle(dir);
                if (db->dirCanOpen(argv[2])){
                    dir = argv[1];
                    db->changeDir(dir, false);
                } else {
                    std::cout <<"Invalid path specified " << argv[1] << " falling back to " << dir << std::endl;
                }
                break;
            }
            case 3:
                port = atoi(argv[2]);
                break;
            case 4:
                commandOffset = 3;
        }
    }
    
    CoreServer *ftpserver = new CoreServer(port,dir, commandOffset);
    
    return (EXIT_SUCCESS);
}

