/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serverconnection.h
 * Author: nguyen trung duc
 *
 * Created on December 5, 2017, 6:58 PM
 */

#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "FTPs.h"
#include "filehandle.h"


class serverconnection {
public:
    serverconnection(int fd, unsigned int connId, std::string defaultDir, std::string hostId, unsigned short commandOffset = 1);
    
    serverconnection(const serverconnection& orig);
    virtual ~serverconnection();
    
    void run();
    void respondToQuery();
    int getFD();
    bool getCloseRequestStatus();
    unsigned int getConnectionId();
    
    std::string commandParser(std::string commad);
    std::vector<std::string> extractParameters(std::string command);
    
private:
    int fd; //for each connection from clinet
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
    filehandle *fh;
    
    unsigned short commandOffset;
    unsigned long receivedPart;
    void sendToClient(char * response, unsigned long length);         
    void sendToclient(std::string response);
    bool commandEquals(std::string a, std::string inString);
    
};

#endif /* SERVERCONNECTION_H */

