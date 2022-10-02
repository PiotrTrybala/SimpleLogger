#include "include/LoggerFormatter.h"

namespace NFCServer {
    namespace Logger {
        
        const std::string LoggerFormatter::FormatMessage(const LoggerLevel& level, const std::string& message, const std::string& format) {
            std::stringstream ss;
            time_t unparsed = time(nullptr);
            struct tm* current_time = localtime(&unparsed);

            auto formatTime = [&](int timeUnit) {
                std::string out = "";
                if (timeUnit < 10) out += "0";
                out += std::to_string(timeUnit);
                return out;
            };

            for (int c = 0; c < format.length(); c++) {
                
                char current = format[c];

                if (current == '%') {
                    c++;
                    switch(format[c]) {
                        // P - message to format
                        case 'P':
                            ss << message;
                            break;
                        // d - single integer
                        case 'd':
                            break;
                        // f - single floating number
                        case 'f':
                            break;
                        // Y - year
                        case 'Y':
                            ss << formatTime(current_time->tm_year + 1900);
                            break;
                        // M - month
                        case 'M':
                            ss << formatTime(current_time->tm_mon + 1);
                            break;
                        // D - day
                        case 'D':
                            ss << formatTime(current_time->tm_mday);
                            break;
                        // H - hour
                        case 'H':
                            ss << formatTime(current_time->tm_hour);
                            break;
                        // m - minute
                        case 'm':
                            ss << formatTime(current_time->tm_min);
                            break;
                        // S - second
                        case 'S':
                            ss << formatTime(current_time->tm_sec);
                            break;
                        // l - logger name
                        case 'l':
                            ss << _loggerName;
                            break;
                        // L - logging level

                        case 'L':  {
                            FormatterColorsBuilder builder;

                            switch(level) {
                                case LoggerLevel::INFO:
                                    builder = builder.AddBuilderMessage("Info")
                                            .Color(ForegroundFormatColor::FG_GREEN);
                                    break;
                                case LoggerLevel::WARN:
                                    builder = builder.AddBuilderMessage("Warn")
                                            .Color(ForegroundFormatColor::FG_YELLOW);
                                    break;
                                case LoggerLevel::ERROR:
                                    builder = builder.AddBuilderMessage("Error")
                                            .Color(ForegroundFormatColor::FG_RED);
                                    break;
                                case LoggerLevel::NONE:
                                    break;
                            }

                            builder = builder.Bold();
                            
                            ss << builder.ToString();

                            break;
                        }
                        default:
                            break;
                    }
                    continue;
                }
                ss << current;
            }
            ss << "\n";
            return ss.str();

        }

    }
}