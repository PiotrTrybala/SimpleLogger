#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/LoggerFormatter.h"

#include "../lib/doctest/doctest/doctest.h"

#include <iostream>

// TODO: fix tests for LoggerFormatter

using namespace NFCServer::Logger;
using namespace std;

const string LoggerName = "SimpleLogger";

TEST_CASE("Simple log without formatting") {

    LoggerFormatter formatter {LoggerName};

    string result = formatter.FormatMessage(LoggerLevel::NONE, "Message");

    CHECK(result == "Message\n");

}

TEST_CASE("Simple log with logger level") {
    LoggerFormatter formatter {LoggerName};
    string formatString = "[%L] Simple message";
    string result = formatter.FormatMessage(LoggerLevel::INFO, formatString, );
    CHECK(result == "[\033[1;32mInfo\033[0m] Simple message\n");

    result = formatter.FormatMessage(LoggerLevel::WARN, formatString);
    CHECK(result == "[\033[1;33mWarn\033[0m] Simple message\n");

    result = formatter.FormatMessage(LoggerLevel::ERROR, formatString);
    CHECK(result == "[\033[1;31mError\033[0m] Simple message\n");

}

TEST_CASE("Simple log with datetime") {

    LoggerFormatter formatter {LoggerName};

    string formatString = "[%Y:%M:%D] {%H:%m:%S} Simple message";

    time_t test_time = time(nullptr);
    struct tm* ct = localtime(&test_time);

    auto formatTime = [&](int timeUnit) {
        std::string out = "";
        if (timeUnit < 10) out += "0";
        out += std::to_string(timeUnit);
        return out;
    };

    string result = formatter.FormatMessage(formatString, LoggerLevel::NONE);

    string compare_string = "[";
    compare_string += formatTime(ct->tm_year + 1900) += ":";
    compare_string += formatTime(ct->tm_mon + 1) += ":";
    compare_string += formatTime(ct->tm_mday) += "] {";

    compare_string += formatTime(ct->tm_hour) += ":";
    compare_string += formatTime(ct->tm_min) += ":";
    compare_string += formatTime(ct->tm_sec) += "} Simple message\n";

    CHECK(compare_string == result);

}

TEST_CASE("Simple log with logger name") {

}