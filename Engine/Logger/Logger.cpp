#include "pch.h"
#include "Logger.h"

#include "../../Logger/Interfaces/ILoggerUnicode.h"
#include "../../Logger/ConsoleLogger/Unicode/ConsoleLoggerUnicode.h"

Logger::~Logger()
{
    delete _logSystem;
}

void Logger::Initialize()
{
}

void Logger::Finalize()
{
}

void Logger::Log(const LogLevel level, const wchar_t* message)
{
    GetInstance()._logSystem->Log(level, message);
}

void Logger::Log(const LogLevel level, const std::wstring& message)
{
    GetInstance()._logSystem->Log(level, message);
}

void Logger::SetLogable(const LogLevel level, const bool logable)
{
    GetInstance()._logSystem->SetLogable(level, logable);
}

void Logger::SetLeastLoglevel(const LogLevel level)
{
    GetInstance()._logSystem->SetLeastLoglevel(level);
}

Logger::Logger() : _logSystem(new ConsoleLoggerUnicode)
{
}

Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}
