// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h>  
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include "msg.h"
#include "port.h"

using namespace std;


socketInfo setUpUDP(int portNum){
	int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(portNum); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    socketInfo retVal;
    retVal.socketNum = sockfd;
    retVal.servaddr = servaddr;
    return retVal;
}

msg requestUDPServer(int port, msg data){
	// serverA connection
    unsigned int len;
	int n; 
    char buffer[1024] = {0}; 
    socketInfo socketA =  setUpUDP (port);
    strcpy (buffer, data.serialize(",").c_str());

    sendto(socketA.socketNum, buffer, strlen(buffer), 
    MSG_CONFIRM, (const struct sockaddr *) &socketA.servaddr,  
        sizeof(socketA.servaddr)); 

    n = recvfrom(socketA.socketNum, (char *)buffer, MAXLINE,  
            MSG_WAITALL, (struct sockaddr *) &socketA.servaddr, 
            &len);
    buffer[n] = '\0'; 
    string line(buffer);
    msg retVal(line, ',');
    return retVal;
}


int main(int argc, char const *argv[]) 
{ 
    cout << "The AWS is up and running" << endl;

    int clientPort = CLIENT_PORT;
    int backAPort = BACKA_PORT;
    int backBPort = BACKB_PORT;
    int backCPort = BACKC_PORT;
    int monitorPort = MONITOR_PORT;
	int socketDist, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	const char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((socketDist = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		cout << "socket failed" << endl;; 
		return 0;
	} 
	
	// Forcefully attaching socket to the port 
	if (setsockopt(socketDist, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		cout << "setsockopt" << endl; 
		return 0; 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( clientPort ); 
	
	// Forcefully attaching socket to the port 
	if (bind(socketDist, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		cout << "bind failed" << endl; 
		return 0;
	} 

	while(true){
		if (listen(socketDist, 3) < 0) 
		{ 
			cout << "listen" << endl;; 
			return 0; 
		} 
		if ((new_socket = accept(socketDist, (struct sockaddr *)&address, 
						(socklen_t*)&addrlen))<0) 
		{ 
			cout << "accept" << endl;; 
			return 0; 
		}

		valread = read( new_socket , buffer, 1024); 
		// printf("%s\n",buffer ); 


        string strBuffer(buffer);
        msg searchRequest(buffer, ',');
        cout << "The AWS received link ID="<< searchRequest.m_linkId<< ", size=" << searchRequest.m_size << ", and power=" << searchRequest.m_power <<"from the client using TCP over port " << clientPort << endl;
        cout << "The AWS sent link ID="<< searchRequest.m_linkId<< ", size=" << searchRequest.m_size << ", and power=" << searchRequest.m_power <<"from the client using TCP over port " << monitorPort << endl;
        cout << "The AWS sent link ID=" << searchRequest.m_linkId << " to Backend-Server " << "A" <<" using UDP over port "<< backAPort << endl;
        msg searchResult = requestUDPServer(backAPort, searchRequest);
        cout << "The AWS received "<< searchResult.m_found << " matches from Backend-Server " << "A" <<" using UDP over port " << backAPort << endl;
        if(!searchResult.isfound()){
            cout << "The AWS sent link ID=" << searchRequest.m_linkId << " to Backend-Server " << "B" <<" using UDP over port"<< backBPort << endl;
        	searchResult = requestUDPServer(backBPort, searchRequest);
            cout << "The AWS received "<< searchResult.m_found << " matches from Backend-Server " << "B" <<" using UDP over port " << backBPort << endl;
        }
        // check if we need to compute
        if(!searchResult.isfound()){
            searchResult.m_found = false;
            strcpy (buffer, searchResult.serialize(",").c_str());
            write(new_socket, (const char*)buffer, sizeof(buffer));
            cout << "The AWS sent No Match to the monitor and the client using TCP over ports " << monitorPort << " and " << clientPort <<", respectively" << endl;
        }
        else{
            searchResult.m_size = searchRequest.m_size;
            searchResult.m_power = searchRequest.m_power;
            msg calculationResult = requestUDPServer(backCPort,searchResult);
            cout << "The AWS sent link ID=" << searchResult.m_linkId<< ", size=" << searchResult.m_size <<", power=" << searchResult.m_power <<", and link information to Backend-Server C using UDP over port " << backCPort << endl;
            cout << "The AWS sent link ID=" << searchResult.m_linkId << ", size=" << searchResult.m_size << ", power=" << searchResult.m_power <<", and link information to Backend-Server C using UDP over port " << backCPort << endl;
            calculationResult.m_found = true;
            strcpy (buffer, calculationResult.serialize(",").c_str());
            write(new_socket, (const char*)buffer, sizeof(buffer));
            cout << "The AWS sent delay="<< calculationResult.m_compute_result <<"ms to the client using TCP over port <port number>" << endl;
        }
        cout << "The AWS sent detailed results to the monitor using TCP over port " <<monitorPort << endl;
        // cout << searchResult.serialize(",") << endl;
    }

         
	//send(new_socket , hello , strlen(hello) , 0 ); 
	return 0; 
} 
