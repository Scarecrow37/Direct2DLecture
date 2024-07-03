#pragma once
#include "../Engine/GameApp.h"

class Player;
class AnimationScene;

class ClientApp final : public GameApp
{
public:
    ClientApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName);

protected:
    void OnUpdate(float deltaTime) override;

private:
    Player* _player;
    std::wstring _drawingObjectCountString;
};
