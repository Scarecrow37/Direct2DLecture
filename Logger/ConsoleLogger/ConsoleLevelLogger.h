#pragma once
#include "../LevelLogger.h"

class ConsoleLevelLogger : public LevelLogger
{
public:
    explicit ConsoleLevelLogger(WORD foreground);
    ConsoleLevelLogger(const ConsoleLevelLogger& other) = default;
    ConsoleLevelLogger(ConsoleLevelLogger&& other) noexcept = default;
    ConsoleLevelLogger& operator=(const ConsoleLevelLogger& other) = default;
    ConsoleLevelLogger& operator=(ConsoleLevelLogger&& other) noexcept = default;
    virtual ~ConsoleLevelLogger() = default;

protected:
    WORD _foreground;
};
