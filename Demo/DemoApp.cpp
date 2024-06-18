#include "DemoApp.h"
#include "../Engine/Renderer/D2DRenderer.h"
#include <d2d1.h>

#include "../Engine/Loader/BitmapLoader.h"
#include "../Engine/Scene/BitmapScene.h"
#include "../Engine/Window/Window.h"

D2D_MATRIX_3X2_F Scale = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F Rotation = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F Translate = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F WorldMatrix = D2D1::Matrix3x2F::Identity();
ID2D1Bitmap* Bitmap = nullptr;

DemoApp::DemoApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* const gameName): GameApp(
    instanceHandle, showCommand, gameName), _bitmapLoader(nullptr)
{

}

void DemoApp::Initialize(const bool isRelease, const Logger::Level leastLogable)
{
    GameApp::Initialize(isRelease, leastLogable);
    _bitmapLoader = new BitmapLoader(_renderer);
    BitmapScene* scene = new BitmapScene(L"../Resources/Images/Solar.png", _bitmapLoader);
    scene->SetTranslation({_window->GetSize().cx / 2.f, _window->GetSize().cy / 2.f});
    scene->SetScale({0.5f, 0.5f});
    AddScene(scene);
    scene->Load();
}
