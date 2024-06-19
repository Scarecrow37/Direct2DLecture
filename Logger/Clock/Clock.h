#pragma once
#include <chrono>

class Clock
{
public:
    static std::time_t GetTime();
    static std::tm GetTimeStruct();
};