#include "pch.h"
#include "LevelLogger.h"

LevelLogger::LevelLogger(): _logable(true)
{
}

void LevelLogger::SetLogable(const bool isLogable)
{
    _logable = isLogable;
}

bool LevelLogger::IsLogable() const
{
    return _logable;
}
