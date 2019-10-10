#include "port.h"
#include "dbclass.h"

using namespace std;

int main(int argc, char const *argv[]) 
{
    dbclass database("B");
    database.openFile("database_b.csv");
    database.runServer(BACKB_PORT);
    return 0;
}