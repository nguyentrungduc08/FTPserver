/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   serverconnection.cpp
 * Author: nguyen trung duc
 * 
 * Created on December 5, 2017, 6:58 PM
 */

#include "../Header/serverconnection.h"

serverconnection::serverconnection(int fd, unsigned int connId, std::string defaultDir, std::string hostID, unsigned short commandOffset) : fd(fd), 
        connectionId(connId), dir(defaultDir), hostAddress(hostID) , commandOffset(commandOffset), closureRequested(false), uploadCommand(false),
        downloadCommand(false), receivedPart(0), parameter("")
{
    this->fh = new filehandle(this->dir);
    std::cout <<"Connection to clinet " << this->hostAddress << " established" << std::endl;
}

serverconnection::serverconnection(const serverconnection& orig) {
}

serverconnection::~serverconnection() {
    std::cout <<"Connection terminated to client (connection id " << this->connectionId << " )" << std::endl;
    delete this->fh;
    close(this->fd);
    this->files.clear();
}

int serverconnection::getFD(){
    return this->fd;
}

bool serverconnection::getCloseRequestStatus(){
    return this->closureRequested;
}

unsigned int serverconnection::getConnectionId(){
    return this->connectionId;
}

//to send string to client using this connnection 
void serverconnection::sendToClient(char* response, unsigned long length){
    unsigned int bytesSend = 0;
    while (bytesSend < length){
        int res = send(this->fd, response + bytesSend, length - bytesSend, 0);
        if (res <= 0){
            return;
        } 
        bytesSend += res;
    }
}

void serverconnection::sendToclient(std::string response){
    unsigned int bytesSend = 0;
    
    while (bytesSend < response.length()){
        int res = send(this->fd, response.c_str() + bytesSend, response.length() - bytesSend, 0);
        if (res <= 0){
            return;
        }
        bytesSend  += res;
    }
}

//this function to receives the incomming data and issues the apropraite commads and responds
void serverconnection::respondToQuery(){
    char buffer[BUFFER_SIZE];
    int bytes;
    bytes = recv(this->fd, buffer, sizeof(buffer), 0);
    
    //in non-blocking model, byte <= 0 does not mean a connection closeure
    
    if (bytes > 0){
        std::string clienCommand = std::string(buffer, bytes);
        
        if (this->uploadCommand){
            std::cout <<"Part " << ++(this->receivedPart) <<": ";
            //this->fh->readFileBlock(clienCommand);
        }
    }
}