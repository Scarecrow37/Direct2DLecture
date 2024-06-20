#include "pch.h"
#include "MultimediaClock.h"
#include <timeapi.h>

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
