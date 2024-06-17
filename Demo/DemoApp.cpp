#include "DemoApp.h"
#include "../Engine/Renderer/D2DRenderer.h"
#include <d2d1.h>

D2D_MATRIX_3X2_F Scale = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F Rotation = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F Translate = D2D1::Matrix3x2F::Identity();
D2D_MATRIX_3X2_F WorldMatrix = D2D1::Matrix3x2F::Identity();
ID2D1Bitmap* Bitmap = nullptr;

DemoApp::DemoApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* const gameName): GameApp(
    instanceHandle, showCommand, gameName)
{
}

void DemoApp::Initialize(const bool isRelease, const Logger::Level leastLogable)
{
    GameApp::Initialize(isRelease, leastLogable);
    Scale = D2D1::Matrix3x2F::Scale(1.f, 1.f);
    Rotation = D2D1::Matrix3x2F::Rotation(0.f);
    Translate = D2D1::Matrix3x2F::Translation(0.f, 0.f);
    _renderer->BitmapFromFile(L"../Resources/Images/atk_1.png", &Bitmap);
}

void DemoApp::OnRender(const D2DRenderer* renderer)
{
    GameApp::OnRender(renderer);
    WorldMatrix = Scale * Rotation * Translate;
    renderer->SetTransform(WorldMatrix);
    renderer->DrawBitmap(Bitmap);
}
