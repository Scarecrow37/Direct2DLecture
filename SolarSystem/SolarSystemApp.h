#pragma once
#include "../Engine/Scenes/BitmapScene.h"

class SolarSystemApp final : public GameApp
{
public:
    SolarSystemApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName);

    void OnInitialize() override;
    void OnUpdate(float deltaTime) override;
    void OnRender(const D2DRenderer* renderer) override;

private:
    BitmapScene _sun;
    BitmapScene _earth;
    BitmapScene _moon;
};
