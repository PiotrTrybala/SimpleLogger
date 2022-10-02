#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "FormatterType.h"



namespace NFCServer {
    namespace Logger {

        class LoggerFormatter {

            private:
                std::string _loggerName;

            public:
                LoggerFormatter(const std::string& loggerName) : _loggerName(loggerName) {}
                ~LoggerFormatter() {}
                LoggerFormatter(const LoggerFormatter& rhs) : _loggerName(rhs._loggerName) {}
                LoggerFormatter operator=(const LoggerFormatter& rhs) {
                    if (this == &rhs) return *this;
                    _loggerName = rhs._loggerName;
                    return *this;
                }

                const std::string FormatMessage(const std::string& message, const LoggerLevel& level);
        };
    }
}