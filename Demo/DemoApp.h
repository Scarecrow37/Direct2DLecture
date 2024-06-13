#pragma once
#include "../Engine/GameApp.h"

class DemoApp final : public GameApp
{
public:
    DemoApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);

    void Initialize(bool isRelease = true) override;

    void OnRender(const D2DRenderer* renderer) override;
};
