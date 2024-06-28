#include "pch.h"
#include "Input.h"

void Input::Initialize(HWND windowHandle)
{
    Input& input = GetInstance();
    input._mouse.Initialize();
    input._mouse.SetWindowHandle(windowHandle);
    input._keyboard.Initialize();
    input._controller.Initialize();
}

void Input::Update()
{
    Input& input = GetInstance();
    input._mouse.Update();
    input._keyboard.Update();
    input._controller.Update();
}

void Input::Reset()
{
    Input& input = GetInstance();
    input._mouse.Reset();
    input._keyboard.Reset();
    input._controller.Reset();
}

bool Input::IsClick(const Mouse::Button button)
{
    return GetInstance()._mouse.IsClick(button);
}

bool Input::IsClickStart(const Mouse::Button button)
{
    return GetInstance()._mouse.IsClickStart(button);
}

bool Input::IsClickEnd(const Mouse::Button button)
{
    return GetInstance()._mouse.IsClickEnd(button);
}

POINT Input::GetMousePosition()
{
    return GetInstance()._mouse.GetMousePosition();
}

POINT Input::GetMouseDeltaPosition()
{
    return GetInstance()._mouse.GetMouseDeltaPosition();
}

Vector Input::GetMouseDirection()
{
    return GetInstance()._mouse.GetMouseDirection();
}

bool Input::IsKey(const unsigned char keyCode)
{
    return GetInstance()._keyboard.IsKey(keyCode);
}

bool Input::IsKeyDown(const unsigned char keyCode)
{
    return GetInstance()._keyboard.IsKeyDown(keyCode);
}

bool Input::IsKeyUp(const unsigned char keyCode)
{
    return GetInstance()._keyboard.IsKeyUp(keyCode);
}

Vector Input::GetAxis(const Controller::Thumb thumb)
{
    return GetInstance()._controller.GetAxis(thumb);
}

float Input::GetTrigger(const Controller::Trigger trigger)
{
    return GetInstance()._controller.GetTrigger(trigger);
}

bool Input::IsControllerButton(const Controller::Button button)
{
    return GetInstance()._controller.IsButton(button);
}

bool Input::IsControllerButtonDown(const Controller::Button button)
{
    return GetInstance()._controller.IsButtonDown(button);
}

bool Input::IsControllerButtonUp(const Controller::Button button)
{
    return GetInstance()._controller.IsButtonUp(button);
}

Input& Input::GetInstance()
{
    static Input input;
    return input;
}
