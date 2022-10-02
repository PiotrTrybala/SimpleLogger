#include "include/Logger.h"

namespace NFCServer {
    namespace Logger {

        void Logger::Print(const LoggerLevel& level, const std::string& message, const std::string& format = DEFAULT_FORMAT) {

            os << _formatter->FormatMessage(level, message, format);

        }

        void Logger::Info(const std::string& message) {
            this->Print(LoggerLevel::INFO, message);
        }

        void Logger::Warn(const std::string& message) {
            this->Print(LoggerLevel::WARN, message);
        }

        void Logger::Error(const std::string& message) {
            this->Print(LoggerLevel::ERROR, message);
        }

    }
}