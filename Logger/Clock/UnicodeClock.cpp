#include "pch.h"
#include "UnicodeClock.h"

UnicodeClock::UnicodeClock(const wchar_t* format) : _format(format)
{
}

wchar_t* UnicodeClock::GetTimeString() const
{
    constexpr size_t bufferSize = 1024;
    wchar_t* buffer = new wchar_t[bufferSize];
    const std::tm timeStruct = GetTimeStruct();
    auto _ = std::wcsftime(buffer, bufferSize, _format, &timeStruct);
    return buffer;
}
