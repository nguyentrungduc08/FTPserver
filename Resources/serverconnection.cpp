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

serverconnection::serverconnection() {
}

serverconnection::serverconnection(const serverconnection& orig) {
}

serverconnection::~serverconnection() {
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