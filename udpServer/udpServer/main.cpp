#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

int SOCK;
int PORT;
struct sockaddr_in SVR_ADDR;
struct sockaddr_in CLI_ADDR;

using namespace std;




int main(int argc, char** argv){
	
	
	//PORT = stoi(argv[1]);
	
	socklen_t msgLength = sizeof(sockaddr);
	int    msgLength2;
	char   msgBuffer[256];
	string msgBufferStr;
	
	
	SVR_ADDR.sin_family      = AF_INET;
	SVR_ADDR.sin_addr.s_addr = INADDR_ANY;
	SVR_ADDR.sin_port        = htons(stoi(argv[1]));
	
  
  
  // create socket
	SOCK = socket(AF_INET, 
                SOCK_DGRAM, 
                0);
	cout << "\nSocket created...";

  // bind to socket
	bind(SOCK, 
       (struct sockaddr*)&SVR_ADDR, 
       sizeof(SVR_ADDR));
	
  cout << "\nBound to socket...\nWaiting for messages from client...";


	while(1){
	    
		// receive message from client
		msgLength2 = recvfrom(SOCK, 
                          (char*)msgBuffer, 
                          256,
                          MSG_WAITALL,
                          (struct sockaddr*)&CLI_ADDR, 
                          &msgLength);
	
		msgBuffer[msgLength2] = '\0';
		cout << "\nClient: " << msgBuffer;
		
		// copy cstring to std::string and transform chars				
    msgBufferStr = string{msgBuffer};		
		transform(msgBufferStr.begin(), 
              msgBufferStr.end(), 
              msgBufferStr.begin(), 
              ::toupper);
				  		
		// send transformed string to client
		sendto(SOCK, 
           (char*)msgBufferStr.c_str(), 
           msgBufferStr.size() + 1,
           MSG_CONFIRM,
           (struct sockaddr*)&CLI_ADDR,
           msgLength);			   
		
    cout << "\nServer: " << msgBufferStr;
	}

  memset(msgBuffer, 0, 256);
  msgBufferStr.clear();
	
	return 0;
}