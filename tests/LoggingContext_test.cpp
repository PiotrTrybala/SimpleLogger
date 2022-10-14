#include "../include/LoggingContext.h"
#include "../include/Logger.h"

using namespace NFCServer::Logger;
using namespace std;

int main() {
    LoggingContext context {};

    Logger serverLogger {"ServerLogger", DEFAULT_FORMAT, true, &context};
    Logger dbLogger {"DbLogger", DEFAULT_FORMAT, true, &context};

    // context.RegisterLogger(serverLogger);
    context.RegisterLogger(dbLogger);

    // context.RunContext();

    // serverLogger.Info("Hello from context!");
    // dbLogger.Warn("Hello from context!");

    // context.StopContext();

    // context.Clear();

    return 0;
}
