#pragma once

class LevelLogger
{
public:
    LevelLogger();

    inline void SetLogable(bool isLogable);
    inline bool IsLogable() const;

private:
    bool _logable;
};
