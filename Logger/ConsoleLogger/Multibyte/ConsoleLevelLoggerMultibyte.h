#pragma once
#include "../ConsoleLevelLogger.h"

class ConsoleLevelLoggerMultibyte final : public ConsoleLevelLogger
{
public:
    ConsoleLevelLoggerMultibyte(const char* name, std::ostream* stream,
                                WORD foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
                                const char* format = "%s %10s\t%s");
    
    void Write(const char* timeString, const char* message) const;

private:
    const char* _name;
    const char* _format;
    std::ostream* _stream;
};
