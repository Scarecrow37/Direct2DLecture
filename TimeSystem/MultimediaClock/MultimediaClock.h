#pragma once

class MultimediaClock final : public ITimeSystem
{
public:
    MultimediaClock() = default;
    float GetDeltaTime() const override;
    void Initialize() override;
    void Update() override;

private:
    DWORD _previousTime;
    DWORD _currentTime;
    DWORD _deltaTime;
};
