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

class CoreServer {
public:
    CoreServer();
    CoreServer(const CoreServer& orig);
    virtual ~CoreServer();
private:
    int start();
    void createSocket(int port);
    void setAttributeSocket(int &sock);
    
    //attribute
    unsigned int maxConnects;
    int s;
    int sflags;
    
};

#endif /* CORESERVER_H */

