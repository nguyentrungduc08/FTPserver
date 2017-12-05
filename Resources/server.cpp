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
    
    int connection, pid, bytes_read;
    
    //server handle
    for(;;){
        //connection = accept(sock, (struct sockaddr*) &client_address, &len );
        char buffer[BSIZE];
        //Command *cmd = malloc(sizeof(Command));
        ///State *state = malloc(sizeof(State));
        
        pid = fork();
        
        memset(buffer, 0 ,sizeof(buffer));
        
        if (pid < 0){
            std::cerr <<"Cannot create child process!!" << std::endl;
            return;
        }
        
        if (pid = 0){
            close(sock);
            std::string hello = "Welcom to FTP server\n";
            
            write(connection, hello.c_str(), sizeof(hello));
            
            while (bytes_read = read(connection, buffer, BSIZE) ){
                
            }
                  
            
        }
    }
}