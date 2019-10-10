#include "computeClass.h"
#include <cmath>
using namespace std;

double computeClass::pdmToWatt(double input){
	input /= 10;
	input = pow(10, input);
	input /= 1000;
	return input;
}

void computeClass::runServer(int portNum){
	cout << "The Server "<< m_name << " is up and running using UDP on port " << portNum << endl;
	// set up the udp connnection
    char buffer[MAXLINE];
    socketInfo socketA =  setUpUDP (portNum);
    struct sockaddr_in cliaddr; 
    //memset(&cliaddr, 0, sizeof(cliaddr)); 

    while(true){
	    unsigned int len = sizeof(struct sockaddr_in);
	    int n;
	    n = recvfrom(socketA.socketNum, (char *)buffer, MAXLINE,  
	                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
	                &len); 
	    buffer[n] = '\0'; 
	    

	    string strBuffer(buffer);
	    msg request(strBuffer, ',');
	    cout << "The Server " << m_name << " received link information of link " << request.m_linkId <<", file size "<< request.m_size <<", and signal power " << request.m_power << endl;

	    // calculation
	    double B = stod(request.m_bandWidth);
	    double S = pdmToWatt(stod(request.m_power));
	    double N = pdmToWatt(stod(request.m_noise));
	    double C = B*log2(1+S/N);
	    double size = stod(request.m_size);
	    double result = size/C;
	    cout << "The server C finished the calculation for link "<<request.m_linkId << endl;
	    msg resultMsg;
	    resultMsg.m_compute_result = to_string(result);

	    strcpy (buffer, resultMsg.serialize(",").c_str());
	    if(sendto(socketA.socketNum, (const char *)buffer, strlen(buffer),  
	        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
	            len)<0){
	            cout << "error sending" << endl;
	    }
	    cout << "The Server "<<m_name<<" finished sending the output to AWS"<< endl;
	}

}