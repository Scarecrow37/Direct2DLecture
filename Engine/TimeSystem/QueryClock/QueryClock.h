#pragma once
#include <Windows.h>
#include "../Interfaces/ITimeSystem.h"

class QueryClock final : public ITimeSystem 
{
public:
    QueryClock();

    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    LARGE_INTEGER _frequency;
    LARGE_INTEGER _previousTick;
    LARGE_INTEGER _currentTick;
    float _deltaTime;
};
