#include "../include/LoggingContext.h"
#include "../include/Logger.h"

using namespace NFCServer::Logger;
using namespace std;

int main() {

    Logger serverLogger {"ServerLogger"};
    Logger dbLogger {"DbLogger"};

    serverLogger.Info("Log");
    dbLogger.Warn("warn");

    serverLogger.Error("Critical error occured");
    dbLogger.Info("Collected 10044 rows.");

    return 0;
}
