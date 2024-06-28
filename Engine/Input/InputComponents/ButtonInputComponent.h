#pragma once

class ButtonInputComponent
{
public:
    ButtonInputComponent();

    void Initialize();
    void Start();
    void End();
    void SetValue(bool value);
    void Reset();

    bool IsOn() const;
    bool IsStarted() const;
    bool IsEnded() const;

private:
    bool _previous;
    bool _current;

    bool _on;
    bool _started;
    bool _ended;
};
