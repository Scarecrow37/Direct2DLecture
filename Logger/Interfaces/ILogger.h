#pragma once

class ILogger abstract
{
public:
    ILogger() = default;
    ILogger(const ILogger& other) = default;
    ILogger(ILogger&& other) noexcept = default;
    ILogger& operator=(const ILogger& other) = default;
    ILogger& operator=(ILogger&& other) noexcept = default;
    virtual ~ILogger() = default;

    virtual void SetLogable(LogLevel level, bool logable) = 0;
    virtual void SetLeastLoglevel(LogLevel level) = 0;
};
