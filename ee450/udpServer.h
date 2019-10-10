#pragma once
#include <unistd.h> 
#include <stdio.h>  
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unistd.h>
#include "msg.h"
#include "port.h"


class udpServer{
public:
	std::string m_name;
	udpServer(std::string name){m_name = name;};
	virtual void runServer(int portNum) = 0;
	socketInfo setUpUDP(int portNum);
};