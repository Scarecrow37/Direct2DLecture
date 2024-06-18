#pragma once
#include <string>

enum class LogLevel;

class ILogger
{
public:
    ILogger(const ILogger& other) = default;
    ILogger(ILogger&& other) noexcept = default;
    ILogger& operator=(const ILogger& other) = default;
    ILogger& operator=(ILogger&& other) noexcept = default;
    virtual ~ILogger() = default;

    virtual void Log(LogLevel level, const char* message) = 0;
    virtual void Log(LogLevel level, const std::string& message) = 0;
    virtual void Log(LogLevel level, const wchar_t* message) = 0;
    virtual void Log(LogLevel level, const std::wstring& message) = 0;
};
