#include "include/Logger.h"
#include "include/GlobalContextInstance.h"

extern NFCServer::Logger::LoggingContext* GetContextInstance();
namespace NFCServer {
    namespace Logger {

        Logger::Logger(const std::string& _loggerName, const std::string &format, bool useLoggingContext) 
            : _name(_loggerName), _format(format), _useLoggingContext(useLoggingContext) {
                _formatter = new LoggerFormatter(_loggerName);
            }
        Logger::~Logger()
        {
            // weak_ptr and shared_ptr is needed
            // delete _context;
            delete _formatter;
        }
        Logger::Logger(const Logger &rhs)
        {
            _formatter = new LoggerFormatter(rhs._name);
            *_formatter = *rhs._formatter;
        }
        Logger& Logger::operator=(const Logger &rhs)
        {
            if (this == &rhs)
                return *this;

            _formatter = new LoggerFormatter(rhs._name);
            // TODO: check if this assignment is necessary
            *_formatter = *rhs._formatter;

            return *this;
        }

        void Logger::Print(const LoggerLevel& level, const std::string& message, const std::string& format = DEFAULT_FORMAT) {
            if (this->_useLoggingContext) {
                GetContextInstance()->Enqueue(_name, level, message, format);
            } else {
                os << _formatter->FormatMessage(level, message, format);
            }
        }

        void Logger::Info(const std::string& message) {
            this->Print(LoggerLevel::INFO, message, _format);
        }

        void Logger::Warn(const std::string& message) {
            this->Print(LoggerLevel::WARN, message, _format);
        }

        void Logger::Error(const std::string& message) {
            this->Print(LoggerLevel::ERROR, message, _format);
        }

    }
}