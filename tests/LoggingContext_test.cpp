#include "../include/Logger.h"
#include "../include/LoggingContext.h"
#include "../include/GlobalContextInstance.h"

using NFCServer::Logger::Logger;
using namespace std;

extern NFCServer::Logger::LoggingContext* NFCServer::Logger::GetContextInstance();
extern void NFCServer::Logger::DestroyInstance();

int main() {

    Logger serverLogger {"ServerLogger", DEFAULT_FORMAT, true};
    Logger dbLogger {"DbLogger", DEFAULT_FORMAT, true};

    NFCServer::Logger::GetContextInstance()->RegisterLogger(serverLogger);

    NFCServer::Logger::GetContextInstance()->RunContext();

    serverLogger.Info("Hello from context!");
    dbLogger.Warn("Hello from context!");

    NFCServer::Logger::GetContextInstance()->StopContext();
    NFCServer::Logger::GetContextInstance()->Clear();

    NFCServer::Logger::DestroyInstance();

    return 0;
}
