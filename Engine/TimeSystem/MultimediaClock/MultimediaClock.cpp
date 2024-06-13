#include "MultimediaClock.h"

#pragma comment (lib, "winmm.lib")

MultimediaClock::MultimediaClock(): _previousTime(0), _currentTime(0), _deltaTime(0)
{
}

float MultimediaClock::GetDeltaTime() const
{
    return static_cast<float>(_deltaTime) / 1000.f;
}

void MultimediaClock::Initialize()
{
    _previousTime = _currentTime = timeGetTime();
}

void MultimediaClock::Update()
{
    _currentTime = timeGetTime();
    _deltaTime = _currentTime - _previousTime;
    _previousTime = _currentTime;
}
