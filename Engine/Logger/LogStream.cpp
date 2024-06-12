#include "LogStream.h"

LogStream::LogStream(const char* path, std::ostream& consoleStream):
    _fileStream(path, std::ios::app),
    _consoleStream(consoleStream),
    _consoleBuffer(consoleStream.rdbuf()),
    _chainBuffer(_consoleBuffer, _fileStream.rdbuf())
{
    _consoleStream.rdbuf(&_chainBuffer);
}

LogStream::~LogStream()
{
    _fileStream.close();
    _consoleStream.rdbuf(_consoleBuffer);
}

std::ostream& LogStream::operator<<(const char* string) const
{
    return _consoleStream << string;
}

