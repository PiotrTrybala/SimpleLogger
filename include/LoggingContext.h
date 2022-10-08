#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <atomic>
#include <map>

#include "Logger.h"
#include "LoggerTypes.h"
#include "TsQueue.h"

namespace NFCServer {
    namespace Logger {
        class Logger;
        class LoggingContext {
            friend class Logger;
            private:
                TsQueue<LogRequest> _dispatchLog;
                std::map<std::string, Logger*> _loggers;
                std::thread* _workerThread;
                std::atomic<bool> _running {true};

                // special logger, not to register
                Logger* _contextLogger;

                void Dispatch(std::string loggerName); 
                void ThreadWorker();
            public:

                LoggingContext();
                ~LoggingContext();
                LoggingContext(LoggingContext& rhs);
                LoggingContext& operator=(const LoggingContext& rhs);

                void Enqueue(std::string loggerName, const LoggerLevel& level, std::string message, std::string format);
                LogRequest Dequeue();



                void RegisterLogger(Logger& logger);
                void RemoveLogger(const std::string& name);

                void RunContext();
                void StopContext();

                

        };

    }
}