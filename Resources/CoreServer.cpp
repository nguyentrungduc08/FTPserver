/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CoreServer.cpp
 * Author: nguyen trung duc
 * 
 * Created on December 5, 2017, 5:48 PM
 */

#include "../Header/CoreServer.h"

CoreServer::CoreServer() {
}

CoreServer::CoreServer(const CoreServer& orig) {
}

CoreServer::~CoreServer() {
}

int CoreServer::start() {
    
}


void CoreServer::createSocket(int port) {
    int reuseable = 1;
    this->maxConnects = 100;
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = INADDR_ANY; //this config to set server can be connected to from any host;
    
    this->socMain  = socket(PF_INET, SOCK_STREAM, 0);
    if (this->socMain == -1){
        std::cerr << "Cannot create socket" << std::endl;
        return;
    }  
    
    if (setsockopt(this->socMain, SOL_SOCKET, SO_REUSEADDR, &reuseable, sizeof(reuseable)) < 0 )
    {
        std::cerr << "setsockopt() fail" << std::endl;
        close(this->socMain);
        return;
    }
    
    this->setAttributeSocket(this->socMain);
    
    if ( bind(this->socMain, (struct sockaddr*) &addr, sizeof(this->addr) ) == -1 ){
        std::cerr << "bind() failed" << std::endl;
        close(this->socMain);
        return;
    }
    if (listen(this->socMain, this->maxConnects) == -1){
        std::cerr << "listen() failed" << std::endl;
        close(this->socMain);
        return;
    }
    
    this->fdmax = this->socMain;
    std::cout << "Server started and listening at port " << port << ", " << std::endl;
    return;
}

/*
 set socket to non-blocking model
 * parameter is reference parameter of main socket 
 */
void CoreServer::setAttributeSocket(int &sock){
    this->sflags = fcntl(sock, F_GETFL);
    int opt = fcntl(sock, F_GETFL, 0);
    
    if (opt < 0){
        std::cerr << "Error getting socket flags" << std::endl;
        return;
    }
    
    opt = (opt | O_NONBLOCK);
    
    if ( fcntl(sock, F_SETFL, opt) < 0){
        std::cerr << "Error setting socket to non-blocking" << std::endl;
        return;
    }
}
