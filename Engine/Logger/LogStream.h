#pragma once
#include <fstream>

#include "ChainStreamBuffer.h"

class LogStream
{
public:
    LogStream(const char* path, std::ostream& consoleStream);
    ~LogStream();

    std::ostream& operator<<(const char* string) const;

private:
    std::ofstream _fileStream;
    std::ostream& _consoleStream;
    std::streambuf* _consoleBuffer;
    ChainStreamBuffer _chainBuffer;
};
