#pragma once

class ITimeSystem
{
public:
    ITimeSystem() = default;
    ITimeSystem(const ITimeSystem& other) = default;
    ITimeSystem(ITimeSystem&& other) noexcept = default;
    ITimeSystem& operator=(const ITimeSystem& other) = default;
    ITimeSystem& operator=(ITimeSystem&& other) noexcept = default;
    virtual ~ITimeSystem() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;

    virtual float GetDeltaTime() const = 0;
};
