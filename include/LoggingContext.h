#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Logger.h"
#include "LoggerTypes.h"
#include "TsQueue.h"
#include <atomic>
#include <map>

namespace NFCServer {
    namespace Logger {
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

                LoggingContext() : _dispatchLog(), _loggers(), _contextLogger() {
                    _contextLogger->_name = "Context";
                    _contextLogger->_useLoggingContext = false;
                }
                ~LoggingContext() {
                    delete _workerThread;
                    delete _contextLogger;
                }
                LoggingContext(LoggingContext& rhs) : _dispatchLog(rhs._dispatchLog), _loggers(rhs._loggers) {
                    _workerThread = new std::thread(rhs._workerThread);
                    // TODO: fix const issue
                    _contextLogger = new Logger(
                        rhs._contextLogger->_name, 
                        rhs._contextLogger->_format,
                        rhs._contextLogger->_useLoggingContext,
                        rhs._contextLogger->_context
                        );
                }

                LoggingContext& operator=(const LoggingContext& rhs) {
                    if (this == &rhs) return *this;
                    _loggers = rhs._loggers;
                    _dispatchLog = rhs._dispatchLog;
                    _workerThread = new std::thread(rhs._workerThread);
                    _contextLogger = new Logger(
                        rhs._contextLogger->_name, 
                        rhs._contextLogger->_format,
                        rhs._contextLogger->_useLoggingContext,
                        rhs._contextLogger->_context
                        );
                    return *this;
                }

                void Enqueue(std::string loggerName, const LoggerLevel& level, std::string message, std::string format);
                LogRequest Dequeue();

                void RegisterLogger(Logger& logger);
                void RemoveLogger(const std::string& name);

                void RunContext();
                void StopContext();

        };

    }
}