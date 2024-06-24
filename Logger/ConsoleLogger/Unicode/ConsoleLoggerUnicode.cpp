#include "pch.h"
#include "ConsoleLoggerUnicode.h"

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

void ConsoleLoggerUnicode::Log(const LogLevel level, const wchar_t* message)
{
    const auto& levelLogger = _levelLoggers.at(level);
    if (!levelLogger.IsLogable() || level < _leastLevel) return;
    const wchar_t* timeString = _clock.GetTimeString();
    levelLogger.Write(timeString, message);
    delete timeString;
}

void ConsoleLoggerUnicode::Log(const LogLevel level, const std::wstring& message)
{
    const auto& levelLogger = _levelLoggers.at(level);
    if (!levelLogger.IsLogable() || level < _leastLevel) return;
    const wchar_t* timeString = _clock.GetTimeString();
    levelLogger.Write(timeString, message.c_str());
    delete timeString;
}

void ConsoleLoggerUnicode::SetLogable(const LogLevel level, const bool logable)
{
    auto& levelLogger = _levelLoggers.at(level);
    levelLogger.SetLogable(logable);
}

void ConsoleLoggerUnicode::SetLeastLoglevel(const LogLevel level)
{
    _leastLevel = level;
}
