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

                void Print(const LoggerLevel& level, const std::string& message, const std::string& format = DEFAULT_FORMAT);
            public:
                Logger(const std::string& _loggerName, const std::string& format = DEFAULT_FORMAT) : _name(_loggerName), _formatter(new LoggerFormatter(_loggerName)) {}
                ~Logger() {
                    delete _formatter;
                }
                Logger(const Logger& rhs) {
                    _formatter = new LoggerFormatter(rhs._name);
                    *_formatter = *rhs._formatter;
                }
                Logger operator=(const Logger& rhs) {
                    if (this == &rhs) return *this;

                    _formatter = new LoggerFormatter(rhs._name);
                    *_formatter = *rhs._formatter;

                    return *this;
                }

                void Info(const std::string& message);
                void Warn(const std::string& message);
                void Error(const std::string& message);
        };

    }
}