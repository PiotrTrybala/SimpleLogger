#include "include/LoggingContext.h"

namespace NFCServer {
    namespace Logger {

        LoggingContext::LoggingContext() : _dispatchLog(), _loggers(), _contextLogger()
        {
            _contextLogger->_name = "Context";
            _contextLogger->_useLoggingContext = false;
        }
        LoggingContext::~LoggingContext()
        {
            delete _workerThread;
            delete _contextLogger;
        }
        LoggingContext::LoggingContext(LoggingContext &rhs) //: _dispatchLog(rhs._dispatchLog), _loggers(rhs._loggers)
        {
            // TODO: fix thread initialization
            // TODO: fix const issue
            _contextLogger = new Logger(
                rhs._contextLogger->_name,
                rhs._contextLogger->_format,
                rhs._contextLogger->_useLoggingContext, rhs._contextLogger->_context);
        }

        LoggingContext &LoggingContext::operator=(const LoggingContext &rhs)
        {
            // TODO: fix thread initialization
            if (this == &rhs)
                return *this;
            _loggers = rhs._loggers;
            _dispatchLog = rhs._dispatchLog;
            _contextLogger = new Logger(
                rhs._contextLogger->_name,
                rhs._contextLogger->_format,
                rhs._contextLogger->_useLoggingContext, rhs._contextLogger->_context);
            return *this;
        }

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
            auto f = [&]() {
                this->ThreadWorker();
            };
            _workerThread = new std::thread(f);
            std::cout << "Started thread with id " << _workerThread->get_id() << std::endl;
        }

        void LoggingContext::StopContext() {
            _running = false;
        }
    }
}