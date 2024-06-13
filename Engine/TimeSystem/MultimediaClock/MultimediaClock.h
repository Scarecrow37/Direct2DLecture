#pragma once
#include <Windows.h>
#include "../Interfaces/ITimeSystem.h"

class MultimediaClock final : public ITimeSystem 
{
public:
    MultimediaClock();
    
    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    DWORD _previousTime;
    DWORD _currentTime;
    DWORD _deltaTime;
};
