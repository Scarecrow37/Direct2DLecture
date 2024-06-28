#pragma once

class ValueInputComponent
{
public:
    ValueInputComponent();

    void Initialize();
    void Reset();

    void SetValue(long value);
    long GetValue() const;
    float GetDirection() const;
    long GetDelta() const;

    void SetSensitivity(long sensitivity);
    void SetDeadZone(float deadZone);

private:
    long _previousValue;
    long _value;
    long _sensitivity;
    float _deadZone;
};
