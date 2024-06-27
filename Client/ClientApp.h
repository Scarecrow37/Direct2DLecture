#pragma once
#include "../Engine/GameApp.h"

class AnimationScene;

class ClientApp final : public GameApp
{
public:
    ClientApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName);
    ~ClientApp() override;

    void OnInitialize() override;
    void OnUpdate(float deltaTime) override;
    void OnRender(const D2DRenderer* renderer) override;

private:
    AnimationScene* _background;
};
