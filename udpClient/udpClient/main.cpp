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

int SOCK;
int PORT;
struct sockaddr_in SVR_ADDR;

using namespace std;

int main(int argc, char** argv){

	
	string message;
	char   msgBuffer[256];
  socklen_t  msgLength;
	

	SVR_ADDR.sin_family = AF_INET;
	SVR_ADDR.sin_addr.s_addr = INADDR_ANY;
	SVR_ADDR.sin_port = htons(stoi(argv[1]));

	
  
  SOCK = socket(AF_INET, SOCK_DGRAM, 0);
	
	
	
	while(1){
		
		cout << "\nEnter message: ";
		getline(cin, message);    
		
		sendto(SOCK, 
           (char*)message.c_str(), 
           message.size()+1, 
           MSG_CONFIRM, 
           (struct sockaddr*)&SVR_ADDR, 
           sizeof(SVR_ADDR));
			   
		recvfrom(SOCK, 
             (char*)msgBuffer, 
             256, 
             MSG_WAITALL, 
             (struct sockaddr*)&SVR_ADDR, 
             &msgLength);

    cout << "Server: " << msgBuffer;

    memset(msgBuffer, 0, 256);
    message.clear();
	}
	
	
	return 0;
}