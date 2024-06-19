#include "pch.h"
#include "MultibyteClock.h"

MultibyteClock::MultibyteClock(const char* format): _format(format)
{
}

char* MultibyteClock::GetTimeString() const
{
    char* buffer = new char[1024];
    const std::tm timeStruct = GetTimeStruct();
    auto _ = std::strftime(buffer, sizeof(buffer), _format, &timeStruct);
    return buffer;
}
