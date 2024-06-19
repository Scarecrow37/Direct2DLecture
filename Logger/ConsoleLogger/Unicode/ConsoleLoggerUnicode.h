#pragma once
#include <map>

#include "ConsoleLevelLoggerUnicode.h"
#include "../../LoggerBase.h"
#include "../../Clock/UnicodeClock.h"

class ConsoleLoggerUnicode final : public LoggerBase, public ILoggerUnicode
{
public:
    ConsoleLoggerUnicode();
    void Log(LogLevel level, const wchar_t* message) override;
    void Log(LogLevel level, const std::wstring& message) override;

private:
    std::map<LogLevel, ConsoleLevelLoggerUnicode> _levelLoggers;
    UnicodeClock _clock;
};
