#include "pch.h"
#include "ConsoleLevelLoggerUnicode.h"

#include <ostream>


ConsoleLevelLoggerUnicode::ConsoleLevelLoggerUnicode(const wchar_t* name, std::wostream* stream, const WORD foreground,
                                                     const wchar_t* format):
    ::ConsoleLevelLogger(foreground), _name(name), _format(format), _stream(stream)
{
}

void ConsoleLevelLoggerUnicode::Write(const wchar_t* timeString, const wchar_t* message) const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _foreground);
    constexpr size_t bufferSize = 1024;
    wchar_t buffer[bufferSize];
    int _ = wprintf_s(buffer, bufferSize, _format, timeString, _name, message);
    *_stream << buffer << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
