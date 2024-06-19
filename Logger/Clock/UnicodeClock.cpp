#include "pch.h"
#include "UnicodeClock.h"

UnicodeClock::UnicodeClock(const wchar_t* format) : _format(format)
{
}

wchar_t* UnicodeClock::GetTimeString() const
{
    wchar_t* buffer = new wchar_t[1024];
    const std::tm timeStruct = GetTimeStruct();
    auto _ = std::wcsftime(buffer, sizeof(buffer), _format, &timeStruct);
    return buffer;
}
