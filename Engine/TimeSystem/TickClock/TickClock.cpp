#include "TickClock.h"

TickClock::TickClock(): _previousTime(0), _currentTime(0), _deltaTime(0)
{
}

float TickClock::GetDeltaTime() const
{
    return static_cast<float>(_deltaTime) / 1000.f;
}

void TickClock::Initialize()
{
    _previousTime = _currentTime = GetTickCount64();
}

void TickClock::Update()
{
    _currentTime = GetTickCount64();
    _deltaTime = _currentTime - _previousTime;
    _previousTime = _currentTime;
}
