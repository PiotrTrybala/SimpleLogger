#include "include/LoggingContext.h"

namespace NFCServer {
    namespace Logger {

        void LoggingContext::Enqueue(std::string loggerName, const LoggerLevel& level, std::string message, std::string format) {
            LogRequest request {loggerName, level, message, format};
            _dispatchLog.Enqueue(request);
        }

        LogRequest LoggingContext::Dequeue() {
            return _dispatchLog.Dequeue();
        }

        void LoggingContext::RegisterLogger(Logger& logger) {
            _loggers.insert(make_pair(
                logger._name,
                &logger
            ));
        }

        void LoggingContext::RemoveLogger(const std::string& name) {
            auto loggerToRemove = _loggers.find(name);
            if (loggerToRemove != _loggers.end()) {
                _loggers.erase(loggerToRemove);
            }
        }

        void LoggingContext::ThreadWorker() {
            while(_running) {
                LogRequest request = Dequeue();
                Logger* currentLogger = _loggers.at(request.LoggerName);
                currentLogger->os << currentLogger->_formatter->FormatMessage(
                    request.LoggingLevel, 
                    request.LogMessage, 
                    request.LogFormat
                    );            
            }
        }

        void LoggingContext::RunContext() {
            _workerThread = new std::thread(ThreadWorker);
            std::cout << "Started thread with id " << _workerThread->get_id() << std::endl;
        }

        void LoggingContext::StopContext() {
            _running = false;
        }
    }
}