#pragma once
#include <string>

enum class LogLevel;

class ILoggerUnicode : public ILogger
{
public:
    virtual void Log(LogLevel level, const wchar_t* message) = 0;
    virtual void Log(LogLevel level, const std::wstring& message) = 0;
};
