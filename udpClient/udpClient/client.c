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
typedef struct hostent hostent;
#define BUFFER_LENGTH 256




int main(int argc, char** argv) 
{
	
  if (argc < 2 || argc == 3 || argc > 4) 
  {
    printf("\nUsage: <port #> -i <ip address>=localhost");
    printf("\nUsage: <port #> -h <hostname>=localhost");
    exit(1);
  }

  hostent*    host;
  sockaddr_in svr_addr;
  socklen_t   msgLength;
	char        msgBuffer[BUFFER_LENGTH];
	char        ip[15];
  int         sock;

  // setup server address parameters
	svr_addr.sin_port   = htons(atoi(argv[1]));
	svr_addr.sin_family = AF_INET;
	
  if(argc > 3 || argv[2] == "-i")
    svr_addr.sin_addr.s_addr = inet_addr(argv[3]);  
  else if (argv[2] == "-h")
  {    
    host = gethostbyname(argv[3]);    
    bcopy((char*)host->h_addr_list[0], (char*)&svr_addr.sin_addr.s_addr, host->h_length);
    svr_addr.sin_addr.s_addr = INADDR_ANY;
  }
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
			   
		recvfrom(sock, (char*)msgBuffer, BUFFER_LENGTH, MSG_WAITALL, 
             (struct sockaddr*)&svr_addr, &msgLength);
    
    printf("Server: %s", msgBuffer);
	}

	return 0;
}