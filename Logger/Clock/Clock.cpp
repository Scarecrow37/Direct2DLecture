#include "pch.h"
#include "Clock.h"

std::time_t Clock::GetTime()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

std::tm Clock::GetTimeStruct()
{
    const auto time = GetTime();
    std::tm tm;
    errno_t _ = localtime_s(&tm, &time);
    return tm;
}
