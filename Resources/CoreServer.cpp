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

#include <arpa/inet.h>

#include "../Header/CoreServer.h"

CoreServer::CoreServer(uint port, std::string dir, unsigned short commandOffset) : dir(dir), commadOffset(commadOffset), shutdown(false), connId(0) {
    if (chdir(dir.c_str())){
        std::cerr << "Directory could not be change to " << dir <<" !!!" << std::endl;
    }
    this->createSocket(port);
    this->start();
}

CoreServer::CoreServer(const CoreServer& orig) {
}

CoreServer::~CoreServer() {
    std::cout << "Server shutdown!!" << std::endl;
    close(this->socMain);
    this->freeAllConnections();
}


void CoreServer::buildSelect(){
    FD_ZERO(&this->working_set);
    
    FD_SET(this->socMain, &this->working_set);
    
    std::vector<serverconnection *> ::iterator iter = this->connections.begin();
    
    while (iter != this->connections.end()){
        if ( (*iter)->getCloseRequestStatus() == true){
            std::cout << "Connection with Id " << (*iter)->getConnectionId() <<  " closed!!" <<std::endl;
            delete(*iter);
            this->connections.erase(iter);
            if (this->connections.empty() || iter == this->connections.end()){
                return;
            }
        } else{
            int currentFD = (*iter)->getFD();
            if (currentFD != 0){
                FD_SET(currentFD, &(this->working_set));
                if (currentFD > this->fdmax)
                    this->fdmax = currentFD;
            }
        }
        ++iter;
    }
}

int CoreServer::start() {
    struct timeval timeout;
    
    int readSocket;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    
    while (!this->shutdown){
        this->buildSelect();
        
        readSocket = select(this->fdmax + 1, &(this->working_set), NULL, NULL, &timeout);
        
        if (readSocket < 0){
            std::cerr <<"time out !!!!!!!!" << std::endl;
            return (EXIT_FAILURE);
        }
       
    }
    
}

int CoreServer::handleNewConnection(){
    int fd;
    
    this->client_size = sizeof(this->client);
    
    fd = accept(this->socMain, (struct sockaddr *) &client, &client_size);
    
    if (fd  < 0){
        std::cerr << "Error while accepting client " << std::endl;
        return (EXIT_FAILURE);
    }
    
    this->setAttributeSocket(fd);
    
    if (fd == -1 ){
        std::cerr << "Something went wrong, new connection could not be handled (Maybe server too busy, too many connections?)" << std::endl;
        try{
            close(fd);
            
        } catch (std::exception e){
            std::cerr << e.what() << std::endl;
        }       
        return (EXIT_FAILURE);
    }
    
    //get client IP address 
    char ipstr[INET6_ADDRSTRLEN];
    int port;
    this->addrLength = sizeof(this->addrStorage);
    
    getpeername(fd, (struct sockaddr*) &this->addrStorage, &(this->addrLength));
    
    std::string hostId = "";
    if (this->addr.sin_family == AF_INET){
        struct sockaddr_in * fd = (struct sockaddr_in*) &(this->addrStorage);
        port = ntohs(fd->sin_port);
        inet_ntop(AF_INET, &fd->sin_addr, ipstr, sizeof(ipstr));
        hostId = (std::string) ipstr;
    }
    
    printf("Connection accepted: FD=%d - Slot=%ld - Id=%u \n", fd, (this->connections.size()+1), ++(this->connId));
    
    serverconnection * conn = new serverconnection(fd, this->connId, this->dir, hostId, this->commadOffset);
    
    this->connections.pb(conn);
    return (EXIT_SUCCESS);
    
}

void CoreServer::freeAllConnections(){
    std::vector<serverconnection*>::iterator iter = this->connections.begin();
    while(iter != this->connections.end()){
        delete(*(iter++));
    }
    this->connections.clear();
}

void CoreServer::readSocketData(){
    
    if (FD_ISSET(this->socMain, &(this->working_set))) {
        
        if (this->handleNewConnection() ) return;
        
    }
    
    for(unsigned int listnum = 0; listnum < this->connections.size(); ++listnum){
        if (FD_ISSET(this->connections.at(listnum)->getFD(),&(this->working_set))) {
            this->connections.at(listnum)->respondToQuery();
        }
    }

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
