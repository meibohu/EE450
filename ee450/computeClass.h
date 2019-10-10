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
#include "udpServer.h"


class computeClass : public udpServer{
public:
	computeClass(std::string name):udpServer(name){}
	void runServer(int portNum);
private:
	double pdmToWatt(double input);
};