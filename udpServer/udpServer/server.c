#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>

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
	char        msgBuffer[256];	
	socklen_t   msgLength = sizeof(sockaddr);
  sockaddr_in svr_addr;
  sockaddr_in cli_addr;
	

  // setup server address parameters
	svr_addr.sin_family      = AF_INET;
	svr_addr.sin_port        = htons(atoi(argv[1]));
  
  struct hostent* host = gethostbyname("cse01.cse.unt.edu"); 
  bcopy((char*)host->h_addr_list[0], (char*)&svr_addr.sin_addr.s_addr, host->h_length);
  //svr_addr.sin_addr.s_addr = INADDR_ANY;
  	     
	
  // create socket and bind to port  
  sock = socket(AF_INET, SOCK_DGRAM, 0);		
  bind(sock, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
	  

	while(1)
  {
    memset(msgBuffer, 0, BUFFER_LENGTH);
    printf("\n\nWaiting for messages from client...");
    fflush(stdout);

		recvfrom(sock, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL,
             (struct sockaddr*)&cli_addr, &msgLength);			
		printf("\n\n\tMessage received: %s", msgBuffer);
				    		    

    for (i = 0; i < strlen(msgBuffer); ++i)     
      msgBuffer[i] = toupper(msgBuffer[i]);    

		
    sendto(sock, (char*)msgBuffer, strlen(msgBuffer), MSG_CONFIRM,
           (struct sockaddr*)&cli_addr, msgLength);			   		
    printf("\n\tMessage sent: %s\n", msgBuffer);
	}

  
	return 0;
}