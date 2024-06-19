#include "pch.h"
#include "ConsoleLevelLoggerMultibyte.h"

#include <ostream>

ConsoleLevelLoggerMultibyte::ConsoleLevelLoggerMultibyte(const char* name, std::ostream* stream, const WORD foreground,
                                                         const char* format):
    ConsoleLevelLogger(foreground), _name(name), _format(format), _stream(stream)
{
}

void ConsoleLevelLoggerMultibyte::Write(const char* timeString, const char* message) const
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _foreground);
    constexpr size_t bufferSize = 1024;
    char buffer[bufferSize];
    int _ = sprintf_s(buffer, bufferSize, _format, timeString, _name, message);
    *_stream << buffer << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
