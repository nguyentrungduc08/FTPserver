/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../Header/FTPs.h"

int createSocket(int port){
    int sock;
    int reuse = 1;
    
    struct sockaddr_in server_address = (struct sockaddr_in) {
        AF_INET, htons(port), (struct in_addr) {INADDR_ANY}
    };
    
    if ( (sock = socket(AF_INET, SOCK_STREAM,0)) < 0){
        std::cerr << "Cannot open socket" << std::endl;
        return -1;
    }
    
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    
    if (bind(sock, (struct sockaddr* ) &server_address, sizeof(server_address) ) < 0){
        std::cerr <<"Cannot bind socket to address" << std::endl;
        return -2;
    }
    
    listen(sock,5);
   
    return sock;
}