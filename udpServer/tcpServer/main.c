

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
  char        msgBuffer[256];
  socklen_t   msgLength = sizeof(struct sockaddr);
  socklen_t   length;
  sockaddr_in svr_addr;
  sockaddr_in cli_addr;


  // setup server address parameters
  svr_addr.sin_family      = AF_INET;
  svr_addr.sin_port        = htons(atoi(argv[1]));
  svr_addr.sin_addr.s_addr = INADDR_ANY;

  socklen_t   c = sizeof(cli_addr);

  // create socket and bind to port  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  tmp = bind(sock, (struct sockaddr*)&svr_addr, length);
  tmp = listen(sock, 1);
  printf("\nListening to socket...\n");
  client_sock = accept(sock, (struct sockaddr*)&cli_addr, &c);
  printf("\nAccepted client...\n");

  while(1)
  {
    memset(msgBuffer, 0, BUFFER_LENGTH);
    printf("\n\nWaiting for messages from client...\n");
    fflush(stdout);

    
    recv(tmp, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL);
    printf("\n\nMessage received: %s\n", msgBuffer);


    for (i = 0; i < strlen(msgBuffer); ++i)     
      msgBuffer[i] = tolower(msgBuffer[i]);    


    send(tmp, (char*)msgBuffer,BUFFER_LENGTH, 0);
    printf("\nMessage sent: %s\n", msgBuffer);
  }

  
  return 0;
}