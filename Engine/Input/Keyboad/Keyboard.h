#pragma once

#include "../InputComponents/ButtonInputComponent.h"

class Keyboard
{
    static constexpr unsigned char NumberOfKeys = 0xFF;

public:
    void Initialize();
    void Update();
    void Reset();

    bool IsKey(unsigned char keyCode) const;
    bool IsKeyDown(unsigned char keyCode) const;
    bool IsKeyUp(unsigned char keyCode) const;

private:
    ButtonInputComponent _keys[NumberOfKeys];
};
