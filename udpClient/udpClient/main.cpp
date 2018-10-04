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
	
	if(argc < 3 || argc > 3){
		cout << "\nUsage: <ip address> <port number>";
	}
	
	string message;
	char   msgBuffer[256];
	
	SOCK = socket(AF_INET, SOCK_DGRAM, 0);
	
	SVR_ADDR.sin_family = AF_INET;
	SVR_ADDR.sin_addr.s_addr = argv[1];
	SVR_ADDR.sin_port = htons(stoi(argv[2]));
	
	
	while(1){
		
		cout << "\nEnter message: ";
		cin >> message;
		
		sendto(SOCK, 
               (char*)&message.c_str(), 
               message.size(), 
               MSG_CONFIRM, 
               (struct sockaddr*)&SVR_ADDR, 
               // ENTER MSGLENGTH
               );
			   
		recvfrom(SOCK, (
	}
	
	
	return 0;
}