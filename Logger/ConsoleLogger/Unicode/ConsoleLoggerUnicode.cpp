#include "pch.h"
#include "ConsoleLoggerUnicode.h"

#include <iostream>

ConsoleLoggerUnicode::ConsoleLoggerUnicode():
    _levelLoggers{
        {LogLevel::Trace, ConsoleLevelLoggerUnicode(L"[TRACE]", &std::wcout)},
        {LogLevel::Debug, ConsoleLevelLoggerUnicode(L"[DEBUG]", &std::wcout)},
        {LogLevel::Information, ConsoleLevelLoggerUnicode(L"[INFO]", &std::wclog)},
        {LogLevel::Warning, ConsoleLevelLoggerUnicode(L"[WARNING]", &std::wclog, FOREGROUND_RED | FOREGROUND_GREEN)},
        {LogLevel::Error, ConsoleLevelLoggerUnicode(L"[ERROR]", &std::wcerr, FOREGROUND_RED | FOREGROUND_BLUE)},
        {LogLevel::Fatal, ConsoleLevelLoggerUnicode(L"[FATAL]", &std::wcerr, FOREGROUND_RED)}
    }
{
}

void ConsoleLoggerUnicode::Log(LogLevel level, const char* message)
{
}

void ConsoleLoggerUnicode::Log(LogLevel level, const std::string& message)
{
}
