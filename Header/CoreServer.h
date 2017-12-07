/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoreServer.h
 * Author: nguyen trung duc
 *
 * Created on December 5, 2017, 5:48 PM
 */

#ifndef CORESERVER_H
#define CORESERVER_H

#include "serverconnection.h"


class CoreServer {
public:
    CoreServer(uint port, std::string dir, unsigned short commandOffset = 1); 
    CoreServer(const CoreServer& orig);
    virtual ~CoreServer();
private:
    int start();
    void createSocket(int port);
    void setAttributeSocket(int &sock);
    void buildSelect();
    void readSocketData();
    //attribute
    unsigned int maxConnects;
    int socMain; //the main listening socket file descripter
    int sflags;
    std::vector<serverconnection *> connections;
    std::string dir;
    unsigned int connId;
    int fdmax;
    fd_set working_set;
    bool shutdown;
    sockaddr_in addr;
    struct sockaddr_storage addrStorage;
    socklen_t addrLength;
    sockaddr_in client;
    socklen_t client_size;
    unsigned short commadOffset;
};

#endif /* CORESERVER_H */

