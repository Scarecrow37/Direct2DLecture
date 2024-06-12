#include "Logger.h"

#include <iostream>
#include "../Utilities/LocalTime.h"
#include "../Utilities/Console.h"


Logger::Logger():

    _traceStream("../Log/Trace.log", std::cout),
    _infoSteam("../Log/Info.log", std::clog),
    _errorStream("../Log/Error.log", std::cerr),
    _levelLoggers{
        {Level::Trace, LevelLogger("[TRACE]", &_traceStream)},
        {Level::Debug, LevelLogger("[DEBUG]", &_traceStream)},
        {Level::Info, LevelLogger("[INFO]", &_infoSteam)},
        {Level::Warning, LevelLogger("[WARNING]", &_infoSteam, FOREGROUND_RED | FOREGROUND_GREEN)},
        {Level::Error, LevelLogger("[ERROR]", &_errorStream, FOREGROUND_RED | FOREGROUND_BLUE)},
        {Level::Fatal, LevelLogger("[FATAL]", &_errorStream, FOREGROUND_RED)}
    },
    _console(nullptr)
{
}

const char* Logger::GetTimeString()
{
    constexpr size_t bufferSize = 1024;
    char* buffer = new char[bufferSize];
    const LocalTime time;
    int _ = sprintf_s(buffer, bufferSize, "[%04d/%02d/%02d %02d:%02d:%02d.%03d]",
                      time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(),
                      time.GetSecond(), time.GetMinute());
    return buffer;
}

Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

Logger::LevelLogger::LevelLogger(const char* name, LogStream* stream, const WORD foreground, const char* format) :
    _name(name), _logStream(stream), _format(format), _logable(true), _foreground(foreground)
{
}

void Logger::LevelLogger::SetLogable(const bool isLogable)
{
    _logable = isLogable;
}

void Logger::LevelLogger::Write(const char* timeString, const char* message) const
{
    Console::SetForegroundColor(_foreground);
    constexpr size_t bufferSize = 1024;
    char buffer[bufferSize];
    int _ = sprintf_s(buffer, bufferSize, _format, timeString, _name, message);
    *_logStream << buffer << std::endl;
    Console::SetForegroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

bool Logger::LevelLogger::IsLogable() const
{
    return _logable;
}

Logger::~Logger()
{
    delete _console;
}

void Logger::Initialize(const bool isOpenConsole)
{
    Logger& logger = GetInstance();
    if (isOpenConsole) logger._console = new Console;
}

void Logger::Log(const Level level, const char* message)
{
    const auto& levelLogger = GetInstance()._levelLoggers.at(level);
    if (!levelLogger.IsLogable()) return;
    const char* timeString = GetTimeString();
    levelLogger.Write(timeString, message);
    delete timeString;
}

void Logger::SetLogable(const Level level, const bool isLogable)
{
    GetInstance()._levelLoggers.at(level).SetLogable(isLogable);
}

void Logger::SetLeastLogable(const Level level)
{
    auto& levelLoggers = GetInstance()._levelLoggers;
    for (auto& logable : levelLoggers)logable.second.SetLogable(true);
    switch (level)
    {
    case Level::Fatal:
        levelLoggers.at(Level::Fatal).SetLogable(false);
    case Level::Error: // NOLINT
        levelLoggers.at(Level::Error).SetLogable(false);
    case Level::Warning: // NOLINT
        levelLoggers.at(Level::Warning).SetLogable(false);
    case Level::Info: // NOLINT
        levelLoggers.at(Level::Info).SetLogable(false);
    case Level::Debug: // NOLINT
        levelLoggers.at(Level::Debug).SetLogable(false);
    case Level::Trace: // NOLINT
        levelLoggers.at(Level::Trace).SetLogable(false);
        break;
    }
    levelLoggers.at(level).SetLogable(true);
}
