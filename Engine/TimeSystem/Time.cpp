#include "Time.h"
#include "MultimediaClock/MultimediaClock.h"
#include "QueryClock/QueryClock.h"
#include "SimpleClock/SimpleClock.h"
#include "TickClock/TickClock.h"

Time::~Time()
{
    delete _timeSystem;
}

void Time::Initialize()
{
    GetInstance()._timeSystem->Initialize();
}

void Time::Update()
{
    GetInstance()._timeSystem->Update();
}

void Time::SetTimeSystem(const TimeSystems timeSystem)
{
    Time& time = GetInstance();
    delete time._timeSystem;
    switch (timeSystem)
    {
    case TimeSystems::MultimediaClock:
        time._timeSystem = new MultimediaClock;
        break;
    case TimeSystems::QueryClock:
        time._timeSystem = new QueryClock;
        break;
    case TimeSystems::SimpleClock:
        time._timeSystem = new SimpleClock;
        break;
    case TimeSystems::TickClock:
        time._timeSystem = new TickClock;
        break;
    }
    time.Initialize();
}

float Time::GetDeltaTime()
{
    return GetInstance()._timeSystem->GetDeltaTime();
}

Time::Time() : _timeSystem(new QueryClock)
{
}

Time& Time::GetInstance()
{
    static Time time;
    return time;
}
