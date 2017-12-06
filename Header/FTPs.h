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
#include <list>
#include <fstream>

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

#define rep(i,n) for(int i = 0; i < n; ++i)
#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define pb push_back
#define mp make_pair

#define BSIZE 1024

struct Command{
    std::string command;
    std::string arg;
};

static std::string welcome_message = "A very warm welcome!";

typedef struct State
{
  /* Connection mode: NORMAL, SERVER, CLIENT */
  int mode;

  /* Is user loggd in? */
  int logged_in;

  /* Is this username allowed? */
  int username_ok;
  char *username;
  
  /* Response message to client e.g. 220 Welcome */
  char *message;

  /* Commander connection */
  int connection;

  /* Socket for passive connection (must be accepted later) */
  int sock_pasv;

  /* Transfer process id */
  int tr_pid;

} State;


typedef enum conn_mode{NORMAL, SERVER, CLIENT} conn_mode;



#endif /* FTPS_H */

