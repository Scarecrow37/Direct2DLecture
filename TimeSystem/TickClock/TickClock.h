#pragma once

class TickClock final : public ITimeSystem
{
public:
    TickClock() = default;

    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    ULONGLONG _previousTime;
    ULONGLONG _currentTime;
    ULONGLONG _deltaTime;
};
