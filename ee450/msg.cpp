#include "msg.h"
#include <sstream>
using namespace std;

msg::msg(bool found, string linkId, string bandwidth, string length, string velocity, string noise ){
        m_found = found;
        m_linkId = linkId;
        m_bandWidth = bandwidth;
        m_length = length;
        m_veclocity = velocity;
        m_noise = noise;
    }
msg::msg(string line, char delimit){
        deserialize(line, delimit);
    }
msg::msg(){
        bool m_found = false;
    }
string msg::serialize(string delimit){
        return to_string(m_found) + delimit + m_linkId + delimit + m_bandWidth + delimit +m_length+delimit+m_veclocity+delimit
        +m_noise + delimit + m_size + delimit + m_power + delimit + m_compute_result;
    }
void msg::deserialize(string line, char delimit){
        stringstream ss(line);
        string temp;
        getline(ss, temp, delimit);
        if(temp == "1"){
            m_found = true;
        }
        else{
            m_found = false;
        }
        getline(ss, m_linkId, delimit);
        getline(ss, m_bandWidth, delimit);
        getline(ss, m_length, delimit);
        getline(ss, m_veclocity, delimit);
        getline(ss, m_noise, delimit);
        getline(ss, m_size, delimit);
        getline(ss, m_power, delimit);
        getline(ss, m_compute_result, delimit);
    }