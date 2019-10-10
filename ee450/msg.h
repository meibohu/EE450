#pragma once
#include <string>
#include <netinet/in.h>

struct socketInfo{
    int socketNum;
    sockaddr_in servaddr;
};


class msg
{
public:
    msg(bool found, std::string linkId, std::string bandwidth, std::string length, std::string velocity, std::string noise );
    msg(std::string line, char delimit);
    msg();
    std::string serialize(std::string delimit);
    void deserialize(std::string line, char delimit);
    bool isfound(){return m_found;}

    bool m_found;
    std::string m_linkId = "";
    std::string m_bandWidth = "";
    std::string m_length = "";
    std::string m_veclocity = "";
    std::string m_noise = "";
    std::string m_size = "";
    std::string m_power = "";
    std::string m_compute_result = "";
};