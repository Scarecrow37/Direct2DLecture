#include "pch.h"
#include "ClientApp.h"

#include <random>

#include "../Engine/Scenes/CameraScene.h"
#include "../Engine/World/World.h"
#include "GameObjects/Monster/Monster.h"
#include "GameObjects/Platform/Platform.h"
#include "GameObjects/Player/Player.h"


ClientApp::ClientApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName)
    : GameApp(instanceHandle, showCommand, gameName),
      _drawingObjectCountString(L"Drawing Objects Count: ")
{
    CameraScene* camera = CameraManager::CreateCamera<CameraScene>(0);
    camera->SetCullingBound(Rect{{0, 0}, _window->GetSize()});
    CameraManager::SetActivatedCamera(camera);
    _player = _world->CreateGameObject<Player>();
    _player->SetCameraScene(camera);
    Monster* monster = _world->CreateGameObject<Monster>();
    monster->SetChaseTarget(_player);
    _world->CreateGameObject<Platform>();
}

void ClientApp::OnUpdate(float deltaTime)
{
}
