#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Logger.h"
#include "LoggerTypes.h"
#include "TsQueue.h"
#include <map>

namespace NFCServer {
    namespace Logger {
        class LoggingContext {
            
            friend class Logger;

            private:
                TsQueue<LogRequest> _dispatchLog;
                std::map<std::string, Logger*> _loggers;

                void Dispatch(std::string loggerName); 
            public:

                LoggingContext() : _dispatchLog(), _loggers() {}
                ~LoggingContext() {}
                LoggingContext(const LoggingContext& rhs) : _dispatchLog(rhs._dispatchLog), _loggers(rhs._loggers) {
                    
                }

                LoggingContext& operator=(const LoggingContext& rhs) {
                    if (this == &rhs) return *this;
                    _loggers = rhs._loggers;
                    _dispatchLog = rhs._dispatchLog;
                    return *this;
                }

                void Enqueue(std::string loggerName, const LoggerLevel& level, std::string message, std::string format);
                LogRequest Dequeue();

                void RegisterLogger(const Logger& logger);
                void RemoveLogger(const std::string& name);

        };

    }
}