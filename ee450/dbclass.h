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


class dbclass : public udpServer{
public:
	dbclass(std::string name):udpServer(name){}
	void openFile(std::string fileName);
	void runServer(int portNum);
private:
	std::unordered_map<std::string, msg> m_map;
};