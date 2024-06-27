#pragma once

enum class LogLevel;
class ILoggerUnicode;

class Logger
{
public:
    Logger(const Logger& other) = delete;
    Logger(Logger&& other) noexcept = delete;
    Logger& operator=(const Logger& other) = delete;
    Logger& operator=(Logger&& other) noexcept = delete;
    ~Logger();
    
    static void Initialize();
    static void Finalize();

    static void Log(LogLevel level, const wchar_t* message);
    static void Log(LogLevel level, const std::wstring& message);
    static void SetLogable(LogLevel level, bool logable);
    static void SetLeastLoglevel(LogLevel level);

private:
    Logger();
    static Logger& GetInstance();

    ILoggerUnicode* _logSystem;
};
