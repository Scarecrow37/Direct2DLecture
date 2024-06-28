#include "pch.h"
#include "Mouse.h"

#include <Windows.h>

Mouse::Mouse() : _windowHandle(nullptr)
{
}

void Mouse::Initialize()
{
    _x.Initialize();
    _y.Initialize();
    _wheel.Initialize();
    for (auto& button : _buttons) button.Initialize();
}

void Mouse::SetWindowHandle(const HWND windowHandle)
{
    _windowHandle = windowHandle;
}

void Mouse::Update()
{
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(_windowHandle, &mousePosition);

    _x.SetValue(mousePosition.x);
    _y.SetValue(mousePosition.y);

    MSG message;
    if (PeekMessage(&message, _windowHandle, NULL, NULL, PM_NOREMOVE)
        && message.message == WM_MOUSEWHEEL)
        _wheel.SetValue(GET_WHEEL_DELTA_WPARAM(message.wParam));

    static bool previousButton[NumberOfMouseButtons];
    static bool currentButton[NumberOfMouseButtons];

    for (unsigned char button = 0; button < NumberOfMouseButtons; ++button)
    {
        currentButton[button] = GetAsyncKeyState(button) & 0x8000;
        if (!previousButton[button] && currentButton[button]) _buttons[button].Start();
        else if (previousButton[button] && !currentButton[button]) _buttons[button].End();
        previousButton[button] = currentButton[button];
    }
}

void Mouse::Reset()
{
    _x.Reset();
    _y.Reset();
    _wheel.Reset();
    for (auto& button : _buttons) button.Reset();
}

bool Mouse::IsClick(Button button) const
{
    return _buttons[static_cast<size_t>(button)].IsOn();
}

bool Mouse::IsClickStart(Button button) const
{
    return _buttons[static_cast<size_t>(button)].IsStarted();
}

bool Mouse::IsClickEnd(Button button) const
{
    return _buttons[static_cast<size_t>(button)].IsEnded();
}

POINT Mouse::GetMousePosition() const
{
    return {_x.GetValue(), _y.GetValue()};
}

POINT Mouse::GetMouseDeltaPosition() const
{
    return {_x.GetDelta(), _y.GetDelta()};
}

Vector Mouse::GetMouseDirection() const
{
    return {_x.GetDirection(), _y.GetDirection()};
}
