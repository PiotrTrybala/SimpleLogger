#pragma once
#include <iostream>
#include <cstdlib>
#include <string>

#include "LoggerFormatter.h"

#define DEFAULT_FORMAT "[%Y/%M/%D %H:%m:%S] {%L} (%l) %P"

namespace NFCServer
{
    namespace Logger
    {
        class Logger
        {
            friend class LoggingContext;

        private:
            string _name;
            string _format;
            LoggerFormatter *_formatter;
            std::ostream &os = std::cout;

            bool _useLoggingContext;

            void Print(const LoggerLevel &level, const std::string &message, const std::string &format);

        public:
            Logger(const std::string& _loggerName, const std::string &format = DEFAULT_FORMAT, bool useLoggingContext = false);
            ~Logger();
            Logger(const Logger &rhs);
            Logger& operator=(const Logger &rhs);

            void Info(const std::string &message);
            void Warn(const std::string &message);
            void Error(const std::string &message);
        };

    }
}