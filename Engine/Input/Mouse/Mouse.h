#pragma once

#include "../InputComponents/ButtonInputComponent.h"
#include "../InputComponents/ValueInputComponent.h"

class Mouse
{
    static constexpr unsigned char NumberOfMouseButtons = 0x06;

public:
    enum class Button : unsigned char
    {
        Left = 0x01,
        Right = 0x02,
        Middle = 0x04,
        X1 = 0x05,
        X2 = 0x06,
    };

public:
    Mouse();

    void SetWindowHandle(HWND windowHandle);
    void Initialize();
    void Update();
    void Reset();

    bool IsClick(Button button) const;
    bool IsClickStart(Button button) const;
    bool IsClickEnd(Button button) const;
    POINT GetMousePosition() const;
    POINT GetMouseDeltaPosition() const;
    Vector GetMouseDirection() const;

private:
    ValueInputComponent _x;
    ValueInputComponent _y;
    ValueInputComponent _wheel;
    ButtonInputComponent _buttons[NumberOfMouseButtons];

    HWND _windowHandle;
};
