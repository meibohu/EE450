#include "port.h"
#include "dbclass.h"

using namespace std;

int main(int argc, char const *argv[]) 
{
    dbclass database("A");
    database.openFile("database_a.csv");
    database.runServer(BACKA_PORT);
    return 0;
}