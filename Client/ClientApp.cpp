#include "pch.h"
#include "ClientApp.h"

#include <random>

#include "../Engine/Scenes/CameraScene.h"
#include "../Engine/World/World.h"
#include "GameObjects/Monster.h"
#include "GameObjects/Player.h"


ClientApp::ClientApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName)
    : GameApp(instanceHandle, showCommand, gameName),
      _drawingObjectCountString(L"Drawing Objects Count: ")
{
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_real_distribution<float> dist(-1920.f, 3840.f);
    CameraScene* camera = CameraManager::CreateCamera<CameraScene>(0);
    camera->SetCullingBound(Rect{{0, 0}, _window->GetSize()});
    CameraManager::SetActivatedCamera(camera);
    _player = _world->CreateGameObject<Player>();
    _player->SetCameraScene(camera);
    for (int i = 0; i < 1000; ++i)
    {
        const Monster* monster = _world->CreateGameObject<Monster>();
        monster->SetTranslation({(dist(mt)), (dist(mt))});
    }
}

void ClientApp::OnUpdate(float deltaTime)
{
    _player->SetCount(_world->GetRenderingObjectCount());
}

// void ClientApp::OnInitialize()
// {
//     srand(time(nullptr));
//     _background->LoadBitmapFromFilename(L"../Resources/Images/midnight.png");
//     _background->LoadAnimationAssetFromFilename(L"../Resources/Animations/Background/Background.csv");
//     // _background->SetScale({static_cast<float>(_window->GetWidth()) / _background->GetAnimationBitmapSize().x, static_cast<float>(_window->GetHeight()) / _background->GetAnimationBitmapSize().y});
//     _background->SetDestinationRect({Vector::Zero(), _window->GetSize()});
// }
//
// void ClientApp::OnUpdate(const float deltaTime)
// {
//     if (Input::IsKeyDown(VK_F1))
//     {
//         AnimationScene* character = new AnimationScene();
//         character->LoadBitmapFromFilename(L"../Resources/Images/run.png");
//         character->LoadAnimationAssetFromFilename(L"../Resources/Animations/Character/Character.csv");
//         character->SetTranslation({
//             static_cast<float>(rand() % _window->GetWidth()), static_cast<float>(rand() % _window->GetHeight())
//         });
//         character->SetMirror(rand() % 2 == 0);
//         _characters.push_back(character);
//     }
//     if (Input::IsKeyDown(VK_F2) && !_characters.empty())
//     {
//         const auto& character = _characters.back();
//         _characters.pop_back();
//         delete character;
//     }
//     _background->Update(deltaTime);
//     for (const auto& character : _characters) character->Update(deltaTime);
//     _vram = _renderer->GetUsedVRAM();
// }
//
// void ClientApp::OnRender(const D2DRenderer* renderer)
// {
//     _background->Render(renderer);
//     for (const auto& character : _characters) character->Render(renderer);
//     _renderer->SetTransform(Matrix::Identity());
//     _renderer->DrawTextW(std::wstring(L"F1: Add Character\nF2: Remove Character"),
//                          20.f, {64.f, 64.f, 516.f, 128.f}, D2D1::ColorF(D2D1::ColorF::White));
//     _renderer->DrawTextW(_vramString + std::to_wstring(_vram),
//                          20.f, {64.f, 128.f, 516.f, 192.f}, D2D1::ColorF(D2D1::ColorF::White));
//     _renderer->DrawTextW(_characterCountString + std::to_wstring(_characters.size()),
//                          20.f, {64.f, 192.f, 516.f, 256.f}, D2D1::ColorF(D2D1::ColorF::White));
// }
