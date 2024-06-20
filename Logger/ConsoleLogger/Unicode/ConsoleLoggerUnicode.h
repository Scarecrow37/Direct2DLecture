#pragma once
#include <map>

#include "ConsoleLevelLoggerUnicode.h"
#include "../ConsoleLogger.h"
#include "../../Clock/UnicodeClock.h"

class ConsoleLoggerUnicode final : public ConsoleLogger, public ILoggerUnicode
{
public:
    ConsoleLoggerUnicode();
    void Log(LogLevel level, const wchar_t* message) override;
    void Log(LogLevel level, const std::wstring& message) override;

private:
    std::map<LogLevel, ConsoleLevelLoggerUnicode> _levelLoggers;
    UnicodeClock _clock;
};
