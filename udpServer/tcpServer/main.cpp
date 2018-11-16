/*
============================================================================
Name        : server.c
Author      : Adam Williams
Course      : CSCE 3530
Copyright   : October 15, 2018
============================================================================
*/

#include <iostream>
#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
#define BUFFER_LENGTH 256




int main(int argc, char** argv)
{

  if (argc < 2 || argc > 2) 
  {
    printf("\nUsage: <port #>");
    exit(1);
  }


  int         i;
  int         sock;
  int         client_sock;
  int         tmp;
  socklen_t   c;
  char        msgBuffer[256];
  socklen_t   msgLength = sizeof(sockaddr);
  sockaddr_in svr_addr;
  sockaddr_in cli_addr;


  // setup server address parameters
  svr_addr.sin_family      = AF_INET;
  svr_addr.sin_port        = htons(atoi(argv[1]));
  svr_addr.sin_addr.s_addr = INADDR_ANY;


  // create socket and bind to port  
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  tmp = bind(sock, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
  tmp = listen(sock, 1);
  printf("\nListening to socket...");
  client_sock = accept(sock, (sockaddr*)&cli_addr, &c);
  printf("\nAccepted client...");

  while(1)
  {
    memset(msgBuffer, 0, BUFFER_LENGTH);
    std::cout << "\n\nWaiting for messages from client..." << std::endl;
    fflush(stdout);

    
    recv(tmp, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL);
    printf("\n\nMessage received: %s", msgBuffer);


    for (i = 0; i < strlen(msgBuffer); ++i)     
      msgBuffer[i] = tolower(msgBuffer[i]);    


    send(tmp, (char*)msgBuffer,BUFFER_LENGTH, 0);
    printf("\nMessage sent: %s\n", msgBuffer);
  }

  
  return 0;
}