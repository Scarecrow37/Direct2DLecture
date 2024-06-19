#pragma once
#include "Clock.h"

class MultibyteClock : public Clock
{
public:
    explicit MultibyteClock(const char* format = "[%Y/%m/%d %H:%M:%S]");
    char* GetTimeString() const;

private:
    const char* _format;
};
