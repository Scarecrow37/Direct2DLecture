#pragma once
#include <Windows.h>
#include "../Interfaces/ITimeSystem.h"

class TickClock final : public ITimeSystem
{
public:
    TickClock();

    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    ULONGLONG _previousTime;
    ULONGLONG _currentTime;
    ULONGLONG _deltaTime;
};
