#include <iostream>

#include "../include/Logger.h"

using namespace NFCServer::Logger;

int main() {

    Logger logger {"SimpleLogger"};

    logger.Info("This is Info message");
    logger.Warn("this is Warn message");
    logger.Error("This is ERROR message");   

    return 0;
}