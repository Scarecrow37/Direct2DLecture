#pragma once

#include "Controller/Controller.h"
#include "Keyboad/Keyboard.h"
#include "Mouse/Mouse.h"

class Input
{
public:
    static void Initialize(HWND windowHandle);
    static void Update();
    static void Reset();

    // Mouse
    static bool IsClick(Mouse::Button button);
    static bool IsClickStart(Mouse::Button button);
    static bool IsClickEnd(Mouse::Button button);
    static POINT GetMousePosition();
    static POINT GetMouseDeltaPosition();
    static Vector GetMouseDirection();

    // Keyboard
    static bool IsKey(unsigned char keyCode);
    static bool IsKeyDown(unsigned char keyCode);
    static bool IsKeyUp(unsigned char keyCode);

    // Controller
    static Vector GetAxis(Controller::Thumb thumb);
    static float GetTrigger(Controller::Trigger trigger);
    static bool IsControllerButton(Controller::Button button);
    static bool IsControllerButtonDown(Controller::Button button);
    static bool IsControllerButtonUp(Controller::Button button);

private:
    static Input& GetInstance();

    Mouse _mouse;
    Keyboard _keyboard;
    Controller _controller;
};
