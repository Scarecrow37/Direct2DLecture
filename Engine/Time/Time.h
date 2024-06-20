#pragma once

class ITimeSystem;

class Time
{
public:
    enum class TimeSystems;

    Time(const Time& other) = delete;
    Time(Time&& other) noexcept = delete;
    Time& operator=(const Time& other) = delete;
    Time& operator=(Time&& other) noexcept = delete;
    virtual ~Time();

    static void Initialize();
    static void Update();
    static void SetTimeSystem(TimeSystems timeSystem);
    static float GetDeltaTime();

private:
    Time();
    static Time& GetInstance();

    ITimeSystem* _timeSystem;

public:
    enum class TimeSystems
    {
        MultimediaClock,
        QueryClock,
        SimpleClock,
        TickClock
    };
};
