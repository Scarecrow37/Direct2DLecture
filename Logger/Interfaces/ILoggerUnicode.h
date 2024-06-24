#pragma once
#include <string>

class ILoggerUnicode abstract : public ILogger
{
public:
    virtual void Log(LogLevel level, const wchar_t* message) = 0;
    virtual void Log(LogLevel level, const std::wstring& message) = 0;
};
