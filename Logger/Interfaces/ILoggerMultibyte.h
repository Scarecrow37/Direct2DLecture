#pragma once

class ILoggerMultibyte abstract : public ILogger
{
public:
    virtual void Log(LogLevel level, const char* message) = 0;
    virtual void Log(LogLevel level, const std::string& message) = 0;
  };

