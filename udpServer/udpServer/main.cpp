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

int SOCK;
int PORT;
struct sockaddr_in SVR_ADDR;
struct sockaddr_in CLI_ADDR;

using std::string;
using std::cout;
using std::transform;

int main(int argc, char** argv){
	
	// first arg should be port #
	if(argc < 2 || argc > 2){
		cout << "\nUsage: <port number>";
	}
	
	PORT = stoi(argv[1]);
	
	int    msgLength;
	int    msgLength2;
	char   msgBuffer[256];
	string msgBufferStr;
	
	
	// create socket
	SOCK = socket(AF_INET, SOCK_DGRAM, 0);
	
	SVR_ADDR.sin_family      = AF_INET;
	SVR_ADDR.sin_addr.s_addr = INADDR_ANY;
	SVR_ADDR.sin_port        = htons(PORT);

	// bind to socket
	bind(SOCK, (struct sockaddr*)&SVR_ADDR, sizeof(SVR_ADDR));
	
	while(1){
	
		// receive message from client
		msgLength2 = recvfrom(SOCK, 
                              (char*)msgBuffer, 
                              256,
                              MSG_WAITALL,
                              (struct sockaddr*)&CLI_ADDR, 
                              &msgLength);
	
		msgBuffer[msgLength2] = '\0';
		
		// copy cstring to std::string and transform chars		
		msgBufferStr = string{msgBuffer};		
		transform(msgBufferStr.begin(), 
                  msgBufferStr.end(), 
                  msgBufferStr.begin(), 
                  ::toupper);
				  
		cout << "\nClient: " << msgBuffer;
		cout << "\nServer: " << msgBufferStr;
		
		
		// send transformed string to client
		sendto(SOCK, 
               (char*)&msgBufferStr.c_str(), 
               msgBufferStr.size(),
               MSG_CONFIRM,
               (struct sockaddr*)&CLI_ADDR,
               msgLength);			   
	}
	
	return 0;
}