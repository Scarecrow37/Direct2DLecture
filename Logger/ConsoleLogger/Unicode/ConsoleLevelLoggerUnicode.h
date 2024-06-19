#pragma once
#include "../ConsoleLevelLogger.h"

class ConsoleLevelLoggerUnicode final : public ConsoleLevelLogger
{
public:
    ConsoleLevelLoggerUnicode(const wchar_t* name, std::wostream* stream,
                              WORD foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
                              const wchar_t* format = L"%s %10s\t%s");

    void Write(const wchar_t* timeString, const wchar_t* message) const;

private:
    const wchar_t* _name;
    const wchar_t* _format;
    std::wostream* _stream;
};
