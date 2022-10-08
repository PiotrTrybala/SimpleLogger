#pragma once
#include "FormatterTypes.h"

namespace NFCServer {
    namespace Logger {

        struct LogRequest {
            std::string LoggerName;
            LoggerLevel LoggingLevel;
            std::string LogMessage;
            std::string LogFormat;

            LogRequest(std::string loggerName, const LoggerLevel level, std::string logMessage, std::string logFormat)
                : LoggerName(loggerName), LoggingLevel(level), LogMessage(logMessage), LogFormat(logFormat) {}

        };

    }
}