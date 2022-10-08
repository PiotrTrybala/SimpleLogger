cmake_minimum_required(VERSION 3.8)

project(SimpleLogger VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set (CPP_SOURCES
    FormatterColorsBuilder.cpp
    LoggerFormatter.cpp
    Logger.cpp
    LoggingContext.cpp
)

add_library(${PROJECT_NAME} ${CPP_SOURCES})