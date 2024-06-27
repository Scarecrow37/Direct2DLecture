#include "pch.h"
#include "ClientApp.h"
#include "../Engine/Scenes/AnimationScene.h"


ClientApp::ClientApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName)
    : GameApp(instanceHandle, showCommand, gameName), _background(new AnimationScene)
{
}

ClientApp::~ClientApp()
{
    delete _background;
}

void ClientApp::OnInitialize()
{
    _background->LoadBitmapFromFilename(L"../Resources/Images/midnight.png");
    _background->LoadAnimationAssetFromFilename(L"../Resources/Animations/Background/Background.csv");
}

void ClientApp::OnUpdate(const float deltaTime)
{
    _background->Update(deltaTime);
}

void ClientApp::OnRender(const D2DRenderer* renderer)
{
    _background->Render(renderer);
}
