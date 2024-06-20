#pragma once

class LevelLogger
{
public:
    LevelLogger();

    void SetLogable(bool isLogable);
    bool IsLogable() const;

private:
    bool _logable;
};
