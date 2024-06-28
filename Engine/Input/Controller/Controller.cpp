#include "pch.h"
#include "Controller.h"

#pragma comment(lib, "xinput.lib")

Controller::Controller(): _controllerIndex(Disconnection)
{
}

void Controller::Initialize()
{
    for (auto& button : _buttons) button.Initialize();

    _leftTrigger.Initialize();
    _leftTrigger.SetSensitivity(TriggerSensitive);
    _rightTrigger.Initialize();
    _rightTrigger.SetSensitivity(TriggerSensitive);

    _leftThumbX.Initialize();
    _leftThumbX.SetSensitivity(ThumbStickSensitive);
    _leftThumbX.SetDeadZone(ThumbDefaultDeadZone);
    _leftThumbY.Initialize();
    _leftThumbY.SetSensitivity(ThumbStickSensitive);
    _leftThumbY.SetDeadZone(ThumbDefaultDeadZone);
    _rightThumbX.Initialize();
    _rightThumbX.SetSensitivity(ThumbStickSensitive);
    _rightThumbX.SetDeadZone(ThumbDefaultDeadZone);
    _rightThumbY.Initialize();
    _rightThumbY.SetSensitivity(ThumbStickSensitive);
    _rightThumbY.SetDeadZone(ThumbDefaultDeadZone);
}

void Controller::Update()
{
    if (_controllerIndex == Disconnection && CheckConnection()) return;
    XINPUT_STATE state{};
    if (XInputGetState(_controllerIndex, &state) != ERROR_SUCCESS)
    {
        _controllerIndex = Disconnection;
        return;
    }

    _leftTrigger.SetValue(state.Gamepad.bLeftTrigger);
    _rightTrigger.SetValue(state.Gamepad.bRightTrigger);

    _leftThumbX.SetValue(state.Gamepad.sThumbLX);
    _leftThumbY.SetValue(state.Gamepad.sThumbLY);
    _rightThumbX.SetValue(state.Gamepad.sThumbRX);
    _rightThumbX.SetValue(state.Gamepad.sThumbRY);

    for (unsigned short button = 0; button < NumberOfControllerButtons; ++button)
    {
        _buttons[button].SetValue(GetFlag(static_cast<Button>(button)) & state.Gamepad.wButtons);
    }
}

void Controller::Reset()
{
    for (auto& button : _buttons) button.Reset();

    _leftTrigger.Reset();
    _rightTrigger.Reset();
    _leftThumbX.Reset();
    _leftThumbY.Reset();
    _rightThumbX.Reset();
    _rightThumbY.Reset();
}

Vector Controller::GetAxis(const Thumb thumb) const
{
    switch (thumb)
    {
    case Thumb::Left:
        return {_leftThumbX.GetDirection(), _leftThumbY.GetDirection()};
    case Thumb::Right:
        return {_rightThumbX.GetDirection(), _rightThumbY.GetDirection()};
    }
    return Vector::Zero();
}

float Controller::GetTrigger(const Trigger trigger) const
{
    switch (trigger)
    {
    case Trigger::Left:
        return _leftTrigger.GetDirection();
    case Trigger::Right:
        return _rightTrigger.GetDirection();
    }
    return 0.f;
}

bool Controller::IsButton(Button button) const
{
    return _buttons[static_cast<int>(button)].IsOn();
}

bool Controller::IsButtonDown(Button button) const
{
    return _buttons[static_cast<int>(button)].IsStarted();
}

bool Controller::IsButtonUp(Button button) const
{
    return _buttons[static_cast<int>(button)].IsEnded();
}

unsigned short Controller::GetFlag(Button button)
{
    int flag = 1;
    for (int i = 0; i < static_cast<int>(button); ++i)
    {
        flag = flag << 1;
    }
    return static_cast<unsigned short>(flag);
}

bool Controller::CheckConnection()
{
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state{};
        const DWORD result = XInputGetState(i, &state);
        if (result == ERROR_SUCCESS)
        {
            _controllerIndex = i;
            break;
        }
    }
    return _controllerIndex != Disconnection;
}
