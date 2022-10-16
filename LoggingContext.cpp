#include "include/LoggingContext.h"

namespace NFCServer {
    namespace Logger {


        // TODO: move background work to BackgroundWorker class
        LoggingContext::LoggingContext() : _dispatchLog(), _loggers(), _contextLogger()
        {
            _contextLogger = new Logger("Context", DEFAULT_FORMAT, false);
        }
        LoggingContext::~LoggingContext()
        {
            _contextLogger->Warn("Clearing LoggingContext");
            // _workerThread.release();
            delete _contextLogger;
        }
        LoggingContext::LoggingContext(LoggingContext &rhs) //: _dispatchLog(rhs._dispatchLog), _loggers(rhs._loggers)
        {
            // TODO: fix thread initialization
            // TODO: fix const issue
            _contextLogger = new Logger(
                rhs._contextLogger->_name,
                rhs._contextLogger->_format,
                rhs._contextLogger->_useLoggingContext);
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
                rhs._contextLogger->_useLoggingContext);
            return *this;
        }

        void LoggingContext::Enqueue(std::string loggerName, const LoggerLevel& level, std::string message, std::string format) {
            std::unique_lock<std::mutex> lock(_dispatchMutex);
            LogRequest request {loggerName, level, message, format};
            _contextLogger->Info("Queued new request: " + loggerName);
            _dispatchLog.Enqueue(request);
        }

        LogRequest LoggingContext::Dequeue() {
            std::unique_lock<std::mutex> lock(_dispatchMutex);
            LogRequest _dequeRequest = _dispatchLog.Dequeue();
            _contextLogger->Info("Dequeued request: " + _dequeRequest.LoggerName);
            return _dequeRequest;
        }

        void LoggingContext::RegisterLogger(Logger& logger) {
            _contextLogger->Info("Registered new logger: " + logger._name);
            _loggers.insert(make_pair(
                logger._name,
                &logger
            ));
        }

        void LoggingContext::RemoveLogger(const std::string& name) {
            _contextLogger->Info("Removed logger: " + name);
            auto loggerToRemove = _loggers.find(name);
            if (loggerToRemove != _loggers.end()) {
                _loggers.erase(loggerToRemove);
            }
        }

        void LoggingContext::ThreadWorker() {
            std::cout << "IsRunning: " << std::boolalpha << _running << std::endl;
            while(_running) {
                if (!_dispatchLog.Empty()) {
                    // std::unique_lock<std::mutex> lock(_dispatchMutex);
                    LogRequest request = Dequeue();
                    _contextLogger->Info("Got request from " + request.LoggerName);
                    Logger* currentLogger = _loggers.at(request.LoggerName);
                    currentLogger->os << currentLogger->_formatter->FormatMessage(
                        request.LoggingLevel,
                        request.LogMessage,
                        request.LogFormat);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));     
            }
        }

        void LoggingContext::RunContext() {
            auto f = [&]() {
                this->ThreadWorker();
            };
            _workerThread.reset(new std::thread(f));

            std::stringstream ss;
            ss << "Started thread with id " << _workerThread->get_id();

            _contextLogger->Info(ss.str());
        }

        void LoggingContext::StopContext() {
            _running = false;
        }

        void LoggingContext::Clear() {
            _workerThread->join();
            _workerThread.release();
        }
    }
}