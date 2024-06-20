#include "pch.h"
#include "QueryClock.h"

QueryClock::QueryClock(): _frequency({}), _previousTick({}), _currentTick({}), _deltaTime(0.f)
{
}

float QueryClock::GetDeltaTime() const
{
    return _deltaTime;
}

void QueryClock::Initialize()
{
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_previousTick);
}

void QueryClock::Update()
{
    QueryPerformanceCounter(&_currentTick);
    _deltaTime = static_cast<float>(_currentTick.QuadPart - _previousTick.QuadPart)
        / static_cast<float>(_frequency.QuadPart);
    _previousTick = _currentTick;
}
