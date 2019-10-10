#include"dbclass.h"

using namespace std;

void dbclass::openFile(string fileName){
    ifstream databaseA(fileName);
    if(databaseA.is_open())
    {
        while(!databaseA.eof()){
            string line;
            getline(databaseA, line);
            line = "1,"+line;
            msg newMsg(line,',');
            m_map[newMsg.m_linkId] = newMsg;
        }
    }
}



void dbclass::runServer(int portNum){
    cout << "The Server "<< m_name <<" is up and running using UDP on port " << portNum << endl;
    // set up the udp connnection
    char buffer[MAXLINE];
    socketInfo socketA =  setUpUDP (portNum);
    struct sockaddr_in cliaddr; 
    //memset(&cliaddr, 0, sizeof(cliaddr)); 


    unsigned int len = sizeof(struct sockaddr_in);
    int n;
    while(true){
        n = recvfrom(socketA.socketNum, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n] = '\0'; 
         
     
        // search from map
        string line(buffer);
        msg request(line, ',');
        cout << "The Server " << m_name << " received input "<< request.m_linkId<< endl;
        auto it = m_map.find(request.m_linkId);
        if(it != m_map.end())
        {
            char outMsg[100];
            strcpy (outMsg, it->second.serialize(",").c_str());
            
            cout << "The server " << m_name <<" has found 1 match" << endl;
            if(sendto(socketA.socketNum, (const char *)outMsg, strlen(outMsg),  
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                len)<0){
                cout << "error sending" << endl;
            }
        }
        else {
            msg tempMsg;
            tempMsg.m_found = false;
            const char * outMsg = tempMsg.serialize(",").c_str();
            cout << "The server " << m_name <<" has found 0 match" << endl;
            if(sendto(socketA.socketNum, (const char *)outMsg, strlen(outMsg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len)<0){
                cout << "error sending" << endl;
            } 
        }
        cout << "The Server "<< m_name <<" finished sending the output to AWS" << endl;

    }

    close(socketA.socketNum);
}