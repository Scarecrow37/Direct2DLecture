#pragma once
#include "../LoggerBase.h"

class ConsoleLogger : public LoggerBase
{
public:
    ConsoleLogger();
    ConsoleLogger(const ConsoleLogger& other) = default;
    ConsoleLogger(ConsoleLogger&& other) noexcept = default;
    ConsoleLogger& operator=(const ConsoleLogger& other) = default;
    ConsoleLogger& operator=(ConsoleLogger&& other) noexcept = default;
    virtual ~ConsoleLogger();
};
