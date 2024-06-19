#pragma once
#include <string>

enum class LogLevel;

class ILoggerUnicode
{
public:
    ILoggerUnicode() = default;
    ILoggerUnicode(const ILoggerUnicode& other) = default;
    ILoggerUnicode(ILoggerUnicode&& other) noexcept = default;
    ILoggerUnicode& operator=(const ILoggerUnicode& other) = default;
    ILoggerUnicode& operator=(ILoggerUnicode&& other) noexcept = default;
    virtual ~ILoggerUnicode() = default;

    virtual void Log(LogLevel level, const wchar_t* message) = 0;
    virtual void Log(LogLevel level, const std::wstring& message) = 0;
};
