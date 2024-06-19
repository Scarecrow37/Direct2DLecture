#pragma once
#include <map>

#include "ConsoleLevelLoggerUnicode.h"
#include "../../LoggerBase.h"
#include "../../Clock/UnicodeClock.h"

class ConsoleLoggerUnicode final : public LoggerBase, public ILoggerMultibyte
{
public:
    ConsoleLoggerUnicode();
    void Log(LogLevel level, const char* message) override;
    void Log(LogLevel level, const std::string& message) override;

private:
    std::map<LogLevel, ConsoleLevelLoggerUnicode> _levelLoggers;
    UnicodeClock _clock;
};
