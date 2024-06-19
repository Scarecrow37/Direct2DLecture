#include "pch.h"
#include "LevelLogger.h"

LevelLogger::LevelLogger(): _logable(true)
{
}

inline void LevelLogger::SetLogable(const bool isLogable)
{
    _logable = isLogable;
}

inline bool LevelLogger::IsLogable() const
{
    return _logable;
}
