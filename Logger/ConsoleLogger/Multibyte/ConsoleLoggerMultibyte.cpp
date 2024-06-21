#include "pch.h"
#include "ConsoleLoggerMultibyte.h"

#include <iostream>

ConsoleLoggerMultibyte::ConsoleLoggerMultibyte():
    _levelLoggers{
        {LogLevel::Trace, ConsoleLevelLoggerMultibyte("[TRACE]", &std::cout)},
        {LogLevel::Debug, ConsoleLevelLoggerMultibyte("[DEBUG]", &std::cout)},
        {LogLevel::Information, ConsoleLevelLoggerMultibyte("[INFO]", &std::clog)},
        {LogLevel::Warning, ConsoleLevelLoggerMultibyte("[WARNING]", &std::clog, FOREGROUND_RED | FOREGROUND_GREEN)},
        {LogLevel::Error, ConsoleLevelLoggerMultibyte("[ERROR]", &std::cerr, FOREGROUND_RED | FOREGROUND_BLUE)},
        {LogLevel::Fatal, ConsoleLevelLoggerMultibyte("[FATAL]", &std::cerr, FOREGROUND_RED)}
    }
{
}

void ConsoleLoggerMultibyte::Log(const LogLevel level, const char* message)
{
    const auto& levelLogger = _levelLoggers.at(level);
    if (!levelLogger.IsLogable() || level < _leastLevel) return;
    const char* timeString = _clock.GetTimeString();
    levelLogger.Write(timeString, message);
    delete timeString;
}

void ConsoleLoggerMultibyte::Log(const LogLevel level, const std::string& message)
{
    const auto& levelLogger = _levelLoggers.at(level);
    if (!levelLogger.IsLogable() || level < _leastLevel) return;
    const char* timeString = _clock.GetTimeString();
    levelLogger.Write(timeString, message.c_str());
    delete timeString;
}

void ConsoleLoggerMultibyte::SetLogable(const LogLevel level, const bool logable)
{
    auto& levelLogger = _levelLoggers.at(level);
    levelLogger.SetLogable(logable);
}

void ConsoleLoggerMultibyte::SetLeastLoglevel(const LogLevel level)
{
    _leastLevel = level;
}
