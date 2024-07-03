﻿#include "pch.h"
#include "BitmapScene.h"

#include "../Renderer/D2DRenderer.h"

BitmapScene::BitmapScene()
    : BitmapScene(nullptr)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor start.");
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::BitmapScene(const Scene* parent)
    : Scene(parent), _bitmap(nullptr)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor start.");
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::~BitmapScene()
{
    Logger::Log(LogLevel::Trace, L"BitmapScene destructor start.");
    ResourceManager::ReleaseD2D1Bitmap(_bitmapPath);
    Logger::Log(LogLevel::Trace, L"BitmapScene destructor end.");
}

void BitmapScene::LoadBitmapFromFilename(const std::wstring& path)
{
    if (_bitmap != nullptr)
    {
        Logger::Log(LogLevel::Warning, L"Bitmap is already loaded.");
        return;
    }
    try
    {
        Logger::Log(LogLevel::Trace, L"BitmapScene load start.");
        _bitmapPath = path;
        ResourceManager::CreateD2D1Bitmap(_bitmapPath, &_bitmap);
        Logger::Log(LogLevel::Trace, L"BitmapScene load end.");
    }
    catch (const Exception& exception) // NOLINT(bugprone-empty-catch)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        _bitmap = nullptr;
        _bitmapPath.clear();
    }
}

Vector BitmapScene::GetBitmapSize() const
{
    return _bitmap->GetSize();
}


void BitmapScene::UpdateCenterTransform()
{
    Logger::Log(LogLevel::Trace, L"BitmapScene update center transform start.");
    _centerMatrix = Matrix::Translation(
        {_bitmap->GetSize().width * -_center.x, _bitmap->GetSize().height * -_center.y});
    Logger::Log(LogLevel::Trace, L"BitmapScene update center transform end.");
}

void BitmapScene::Update(const float deltaTime)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene update start.");
    UpdateTransform();
    Logger::Log(LogLevel::Trace, L"BitmapScene update end.");
}

void BitmapScene::Render(const D2DRenderer* renderer) const
{
    Logger::Log(LogLevel::Trace, L"BitmapScene render start.");
    if (_bitmap == nullptr)
    {
        Logger::Log(LogLevel::Information, L"Bitmap is not loaded.");
        return;
    }
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawBitmap(_bitmap);
    Logger::Log(LogLevel::Trace, L"BitmapScene render end.");
}
