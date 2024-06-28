#include "pch.h"
#include "Keyboard.h"

void Keyboard::Initialize()
{
    for (auto& key : _keys) key.Initialize();
}

void Keyboard::Update()
{
    static bool previousKey[NumberOfKeys];
    static bool currentKey[NumberOfKeys];

    for (unsigned char key = 0; key < NumberOfKeys; ++key)
    {
        currentKey[key] = GetAsyncKeyState(key) & 0x8000;
        if (!previousKey[key] && currentKey[key]) _keys[key].Start();
        else if (previousKey[key] && !currentKey[key]) _keys[key].End();
        previousKey[key] = currentKey[key];
    }
}

void Keyboard::Reset()
{
    for (auto& key : _keys) key.Reset();
}

bool Keyboard::IsKey(const unsigned char keyCode) const
{
    return _keys[keyCode].IsOn();
}

bool Keyboard::IsKeyDown(const unsigned char keyCode) const
{
    return _keys[keyCode].IsStarted();
}

bool Keyboard::IsKeyUp(const unsigned char keyCode) const
{
    return _keys[keyCode].IsEnded();
}
