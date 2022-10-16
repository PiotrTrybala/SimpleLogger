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
    Logger timerLogger {"TimerLogger", DEFAULT_FORMAT, true};

    NFCServer::Logger::GetContextInstance()->RegisterLogger(serverLogger);
    NFCServer::Logger::GetContextInstance()->RegisterLogger(dbLogger);
    NFCServer::Logger::GetContextInstance()->RegisterLogger(timerLogger);

    // TODO: fix blocking the thread and fix ThreadWorker function in LoggingContext

    NFCServer::Logger::GetContextInstance()->RunContext();

    serverLogger.Info("Hello from context!");
    dbLogger.Warn("Hello from context!");

    char q = '\0';
    while(true) {
        cin >> q;
        if (q == 'q') {
            NFCServer::Logger::GetContextInstance()->StopContext();
            break;
        }
    }
    
    NFCServer::Logger::GetContextInstance()->Clear();
    NFCServer::Logger::DestroyInstance();

    return 0;
}
