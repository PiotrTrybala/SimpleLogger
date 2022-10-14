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

    auto f = [&timerLogger]() {
        while(true) {
            timerLogger.Info("Timer executes each 1 second");
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        
    };

    NFCServer::Logger::GetContextInstance()->RegisterLogger(serverLogger);
    NFCServer::Logger::GetContextInstance()->RegisterLogger(dbLogger);
    NFCServer::Logger::GetContextInstance()->RegisterLogger(timerLogger);

    thread t(f);

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

    t.join();

    NFCServer::Logger::GetContextInstance()->Clear();
    NFCServer::Logger::DestroyInstance();

    return 0;
}
