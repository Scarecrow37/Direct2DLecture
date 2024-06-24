#pragma once

class LevelLogger abstract
{
public:
    LevelLogger();

    void SetLogable(bool isLogable);
    bool IsLogable() const;

private:
    bool _logable;
};
