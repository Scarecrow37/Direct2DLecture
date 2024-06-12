#pragma once
#include "../Framework.h"

class LocalTime
{
public:
    LocalTime();
    WORD GetYear() const;
    WORD GetMonth() const;
    WORD GetDay() const;
    WORD GetDayOfWeek() const;
    WORD GetHour() const;
    WORD GetMinute() const;
    WORD GetSecond() const;
    WORD GetMillisecond() const;

private:
    SYSTEMTIME _time;
};
