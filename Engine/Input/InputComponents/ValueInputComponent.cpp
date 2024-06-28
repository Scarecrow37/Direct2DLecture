#include "pch.h"
#include "ValueInputComponent.h"

template <typename T>
T Clamp(T value, T min, T max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

ValueInputComponent::ValueInputComponent(): _previousValue(0), _value(0), _sensitivity(100), _deadZone(0)
{
}

void ValueInputComponent::SetValue(const long value)
{
    _value = value;
}

long ValueInputComponent::GetValue() const
{
    return _value;
}

float ValueInputComponent::GetDirection() const
{
    const long offset = _value - _previousValue;
    const float ratio = static_cast<float>(offset) / static_cast<float>(_sensitivity);
    if (std::abs(ratio) < _deadZone) return 0.f;
    return ratio;
}

long ValueInputComponent::GetDelta() const
{
    return _value - _previousValue;
}

void ValueInputComponent::Reset()
{
    _previousValue = _value;
    _value = 0;
}

void ValueInputComponent::Initialize()
{
    _previousValue = 0;
    _value = 0;
}

void ValueInputComponent::SetSensitivity(const long sensitivity)
{
    _sensitivity = sensitivity;
}

void ValueInputComponent::SetDeadZone(const float deadZone)
{
    _deadZone = Clamp(deadZone, 0.f, 1.f);
}
