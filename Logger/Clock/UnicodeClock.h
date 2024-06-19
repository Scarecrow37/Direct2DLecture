#pragma once
#include "Clock.h"

class UnicodeClock : public Clock
{
public:
    explicit UnicodeClock(const wchar_t* format = L"[%Y/%m/%d %H:%M:%S]");
    wchar_t* GetTimeString() const;

private:
    const wchar_t* _format;
};
