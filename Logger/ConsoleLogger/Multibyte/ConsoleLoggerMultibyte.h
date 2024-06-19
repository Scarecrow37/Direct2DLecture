#pragma once
#include <map>

#include "ConsoleLevelLoggerMultibyte.h"
#include "../../LoggerBase.h"
#include "../../Clock/MultibyteClock.h"

class ConsoleLoggerMultibyte final : public LoggerBase, public ILoggerMultibyte
{
public:
    ConsoleLoggerMultibyte();
    void Log(LogLevel level, const char* message) override;
    void Log(LogLevel level, const std::string& message) override;

private:
    std::map<LogLevel, ConsoleLevelLoggerMultibyte> _levelLoggers;
    MultibyteClock _clock;
};
