

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h> 
#include <netinet/ip.h>
#include <sys/stat.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct hostent hostent;
#define BUFFER_LENGTH 256




int main(int argc, char** argv) 
{

  if (argc < 3 || argc > 3) 
  {
    printf("\nUsage: hostname <port #>");
    exit(1);
  }

  sockaddr_in svr_addr;
  socklen_t   msgLength;
  char        msgBuffer[BUFFER_LENGTH];
  int         sock;
  hostent*    server;

  server = gethostbyname(argv[1]);
  
  // setup server address parameters
  bzero((char*)&svr_addr,sizeof(svr_addr));  
  bcopy((char*)server->h_addr_list[0],
    (char*)&svr_addr.sin_addr.s_addr,server->h_length);  
  svr_addr.sin_family      = AF_INET;
  svr_addr.sin_port        = htons(atoi(argv[2]));  

  
  // create socket  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  connect(sock, (sockaddr*)&svr_addr, sizeof(svr_addr));



  while(1)
  {
    memset(msgBuffer, 0, BUFFER_LENGTH);    
    printf("\n\nEnter message: ");
    gets(msgBuffer);     


    send(sock, (char*)msgBuffer, strlen(msgBuffer), 0);
   
    recv(sock, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL);
    
    printf("Server: %s", msgBuffer);
  }

  return 0;
}