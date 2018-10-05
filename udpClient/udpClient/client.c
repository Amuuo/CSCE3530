#include <stdio.h> 
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
	
  if (argc < 2 || argc > 3) 
  {
    printf("\nUsage: <port #> <ip address>=localhost");
    exit(1);
  }


  sockaddr_in svr_addr;
  socklen_t   msgLength;
	char        msgBuffer[BUFFER_LENGTH];
  int         sock;
	

  // setup server address parameters
	svr_addr.sin_port   = htons(atoi(argv[1]));
	svr_addr.sin_family = AF_INET;
	
  if(argc > 2)
    svr_addr.sin_addr.s_addr = argv[2];  
  else
    svr_addr.sin_addr.s_addr = INADDR_ANY;

  
  // create socket  
  sock = socket(AF_INET, SOCK_DGRAM, 0);
	



	while(1)
  {		
    memset(msgBuffer, 0, BUFFER_LENGTH);    
		printf("\n\nEnter message: ");
		gets(msgBuffer);         
		
		sendto(sock, (char*)msgBuffer, strlen(msgBuffer)+1, MSG_CONFIRM, 
           (struct sockaddr*)&svr_addr, sizeof(svr_addr));
		printf("\033\033");
    printf("Sent: %s", msgBuffer);	   
		
    recvfrom(sock, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL, 
             (struct sockaddr*)&svr_addr, &msgLength);
    printf("Server: %s", msgBuffer);
	}

	return 0;
}