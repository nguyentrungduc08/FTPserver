/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../Header/FTPs.h"

void serverFTP(int port){
    int sock = createSocket(port);
    struct sockaddr_in client_address;
    int len = sizeof(client_address);
    
    //server handle
    for(;;){
        
    }
}