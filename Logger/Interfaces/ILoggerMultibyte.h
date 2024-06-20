#pragma once
#include <string>

enum class LogLevel;

class ILoggerMultibyte
{
public:
    ILoggerMultibyte() = default;
    ILoggerMultibyte(const ILoggerMultibyte& other) = default;
    ILoggerMultibyte(ILoggerMultibyte&& other) noexcept = default;
    ILoggerMultibyte& operator=(const ILoggerMultibyte& other) = default;
    ILoggerMultibyte& operator=(ILoggerMultibyte&& other) noexcept = default;
    virtual ~ ILoggerMultibyte() = default;

    virtual void Log(LogLevel level, const char* message) = 0;
    virtual void Log(LogLevel level, const std::string& message) = 0;
  };
