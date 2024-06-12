#pragma once

#include <map>
#include "../Framework.h"
#include "LogStream.h"

class Console;

class Logger
{
public:
    enum class Level
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

private:
    class LevelLogger
    {
    public:
        LevelLogger(const char* name, LogStream* stream,
                    WORD foreground = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
                    const char* format = "%s %10s\t%s");
        void SetLogable(bool isLogable);
        void Write(const char* timeString, const char* message) const;
        bool IsLogable() const;

    private:
        const char* _name;
        LogStream* _logStream;
        const char* _format;
        bool _logable;
        WORD _foreground;
    };

public:
    ~Logger();

    static void Initialize(bool isOpenConsole = false);
    static void Log(Level level, const char* message);
    static void SetLogable(Level level, bool isLogable);
    static void SetLeastLogable(Level level);

private:
    Logger();

    static const char* GetTimeString();

    static Logger& GetInstance();

    LogStream _traceStream;
    LogStream _infoSteam;
    LogStream _errorStream;
    std::map<Level, LevelLogger> _levelLoggers;
    Console* _console;
};
