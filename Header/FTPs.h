/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FTPs.h
 * Author: Nguyen Trung Duc
 *
 * Created on December 4, 2017, 3:13 PM
 */

#ifndef FTPS_H
#define FTPS_H


#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <netinet/in.h>

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <signal.h>

#include <openssl/bio.h>

int createSocket(int port);



#endif /* FTPS_H */

