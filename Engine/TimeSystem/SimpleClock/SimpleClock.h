#pragma once
#include <ctime>
#include "../Interfaces/ITimeSystem.h"

class SimpleClock final : public ITimeSystem
{
public:
    SimpleClock();

    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    clock_t _previousClock;
    clock_t _currentClock;
    clock_t _deltaClock;
};
