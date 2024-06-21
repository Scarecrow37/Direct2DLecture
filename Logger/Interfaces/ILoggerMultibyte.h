#pragma once

enum class LogLevel;

class ILoggerMultibyte : public ILogger
{
public:
    virtual void Log(LogLevel level, const char* message) = 0;
    virtual void Log(LogLevel level, const std::string& message) = 0;
  };

