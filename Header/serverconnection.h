/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serverconnection.h
 * Author: hydra
 *
 * Created on December 5, 2017, 6:58 PM
 */

#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "FTPs.h"

class serverconnection {
public:
    serverconnection();
    serverconnection(const serverconnection& orig);
    virtual ~serverconnection();
    
    void run();
    void respondToQuery();
    int getFD();
    bool getCloseRequestStatus();
    unsigned int getConnectionId();

private:
    int fd; 
    int fdflags;
    bool closureRequested;
    std::vector<std::string> directories;
    std::vector<std::string> files;
    unsigned int connectionId;
    std::string dir;
    std::string hostAddress;
    bool uploadCommand;
    bool downloadCommand;
    std::string parameter;
    
};

#endif /* SERVERCONNECTION_H */

