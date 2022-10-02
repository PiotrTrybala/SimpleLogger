#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/FormatterColorsBuilder.h"

#include "../lib/doctest/doctest/doctest.h"

#include <iostream>

using namespace NFCServer::Logger;
using namespace std;

TEST_CASE("output without any styles") {
    FormatterColorsBuilder builder {"Test string"};
    string result = builder.ToString();
    CHECK(result == "Test string\n");
}

TEST_CASE("output with red color only") {
    FormatterColorsBuilder builder {"Test string"};
    builder.Color(ForegroundFormatColor::FG_RED);
    string result = builder.ToString();
    CHECK(result == "\033[31mTest string\033[0m\n");
}

TEST_CASE("output with bold only") {
    FormatterColorsBuilder builder {"Test string"};
    builder.Bold();
    string result = builder.ToString();
    CHECK(result == "\033[1mTest string\033[0m\n");
}

TEST_CASE("output with bold + yellow foreground + green background") {
    FormatterColorsBuilder builder {"Test string"};
    builder.Color(ForegroundFormatColor::FG_YELLOW, BackgroundFormatColor::BG_GREEN);
    builder.Bold();
    string result = builder.ToString();
    CHECK(result == "\033[1;33;42mTest string\033[0m\n");
}