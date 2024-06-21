#pragma once
#include "../Engine/Scene/BitmapScene.h"

class SolarSystemApp final : public GameApp
{
public:
    SolarSystemApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName,
                   const std::shared_ptr<ILoggerUnicode>& logger);

    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(const D2DRenderer& renderer) override;

private:
    BitmapScene _sun;
    BitmapScene _earth;
    BitmapScene _moon;
};
