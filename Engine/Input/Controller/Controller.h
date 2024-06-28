#pragma once
#include <Xinput.h>

#include "../InputComponents/ButtonInputComponent.h"
#include "../InputComponents/ValueInputComponent.h"

class Controller
{
    static constexpr DWORD Disconnection = -1;
    static constexpr long ThumbStickSensitive = 32767;
    static constexpr float ThumbDefaultDeadZone = 0.1f;
    static constexpr long TriggerSensitive = 255;
    static constexpr unsigned short NumberOfControllerButtons = 16;

public:
    enum class Button
    {
        DpadUp,
        DpadDown,
        DpadLeft,
        DpadRight,
        Start,
        Back,
        LeftThumb,
        RightThumb,
        LeftShoulder,
        RightShoulder,
        Padding1,
        Padding2,
        A,
        B,
        X,
        Y,
    };

    enum class Trigger
    {
        Left,
        Right
    };

    enum class Thumb
    {
        Left,
        Right
    };;

public:
    Controller();
    void Initialize();
    void Update();
    void Reset();

    Vector GetAxis(Thumb thumb) const;
    float GetTrigger(Trigger trigger) const;
    bool IsButton(Button button) const;
    bool IsButtonDown(Button button) const;
    bool IsButtonUp(Button button) const;

private:
    static unsigned short GetFlag(Button button);

    bool CheckConnection();

    DWORD _controllerIndex;

    ButtonInputComponent _buttons[NumberOfControllerButtons];

    ValueInputComponent _leftTrigger;
    ValueInputComponent _rightTrigger;
    ValueInputComponent _leftThumbX;
    ValueInputComponent _leftThumbY;
    ValueInputComponent _rightThumbX;
    ValueInputComponent _rightThumbY;
};
