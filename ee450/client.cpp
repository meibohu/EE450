#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "msg.h"
#include "port.h"
#include <iostream> 

using namespace std;
   
int main(int argc, char const *argv[]) 
{ 
    cout << "The client is up and running" << endl;

    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(CLIENT_PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    cout << "The client sent ID=" << argv[1] <<", size=" << argv[2] <<", and power=" << argv[3] << " to AWS \n" ;

    char str[80];
    strcpy(str, argv[1]);
    strcat(str, ",");
    strcat(str, argv[2]);
    strcat(str, ",");
    strcat(str, argv[3]);
    string linkId(argv[1]);
    string size(argv[2]);
    string power(argv[3]);
    msg request;
    request.m_linkId = linkId;
    request.m_size = size;
    request.m_power = power;

    strcpy (buffer, request.serialize(",").c_str());
    send(sock,buffer,strlen(buffer),0);
    bzero(buffer, sizeof(buffer)); 

    valread = read( sock , buffer, 1024); 
    string line(buffer);
    msg result(line, ',');
    if(result.isfound()){
        cout << "The delay for link "<< result.m_linkId << " is "<< result
        .m_compute_result<<"ms" << endl;
    }
    else{
        cout << "Found no matches for link " << result.m_linkId << endl;
    }
    return 0; 
}  
