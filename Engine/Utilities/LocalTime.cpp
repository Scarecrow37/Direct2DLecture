#include "LocalTime.h"
#include "sysinfoapi.h"

LocalTime::LocalTime() : _time({})
{
    GetLocalTime(&_time);
}

WORD LocalTime::GetYear() const
{
    return _time.wYear;
}

WORD LocalTime::GetMonth() const
{
    return _time.wMonth;
}

WORD LocalTime::GetDay() const
{
    return _time.wDay;
}

WORD LocalTime::GetDayOfWeek() const
{
    return _time.wDayOfWeek;
}

WORD LocalTime::GetHour() const
{
    return _time.wHour;
}

WORD LocalTime::GetMinute() const
{
    return _time.wMinute;
}

WORD LocalTime::GetSecond() const
{
    return _time.wSecond;
}

WORD LocalTime::GetMillisecond() const
{
    return _time.wMilliseconds;
}
