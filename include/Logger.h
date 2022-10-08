#include <iostream>
#include <cstdlib>
#include <string>

#include "LoggerFormatter.h"

#define DEFAULT_FORMAT "[%Y/%M/%D %H:%m:%S] {%L} (%l) %P"

namespace NFCServer {
    namespace Logger {

        class Logger {
            private:

                string _name;
                LoggerFormatter* _formatter;
                std::ostream& os = std::cout;

                bool _useLoggingContext;
                LoggingContext* _context;

                void Print(const LoggerLevel& level, const std::string& message, const std::string& format);
            public:
                Logger(const std::string& _loggerName, const std::string& format = DEFAULT_FORMAT, bool useLoggingContext = false, LoggingContext* ctx = nullptr) : _name(_loggerName), _formatter(new LoggerFormatter(_loggerName)), _useLoggingContext(useLoggingContext), _context(ctx) {}
                ~Logger() {
                    delete _context;
                    delete _formatter;
                }
                Logger(const Logger& rhs) {
                    _formatter = new LoggerFormatter(rhs._name);
                    *_formatter = *rhs._formatter;
                    _context = new LoggingContext();
                    *_context = *rhs._context;
                }
                Logger operator=(const Logger& rhs) {
                    if (this == &rhs) return *this;

                    _formatter = new LoggerFormatter(rhs._name);
                    // TODO: check if this assignment is necessary
                    *_formatter = *rhs._formatter;

                    _context = new LoggingContext();
                    *_context = *rhs._context;
                    
                    return *this;
                }

                void Info(const std::string& message);
                void Warn(const std::string& message);
                void Error(const std::string& message);
        };

    }
}