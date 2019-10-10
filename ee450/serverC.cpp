#include "port.h"
#include "computeClass.h"

using namespace std;

int main(int argc, char const *argv[]) 
{
    computeClass server("C");
    server.runServer(BACKC_PORT);
    return 0;
}