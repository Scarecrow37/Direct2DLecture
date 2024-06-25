#include "pch.h"
#include "BitmapScene.h"

#include "../Renderer/D2DRenderer.h"

BitmapScene::BitmapScene()
    : BitmapScene(nullptr)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor start.");
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::BitmapScene(const Scene* parent)
    : Scene(parent), _center(0.f, 0.f), _centerMatrix(D2D1::Matrix3x2F::Identity()), _bitmap(nullptr)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor start.");
    Logger::Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::~BitmapScene()
{
    Logger::Log(LogLevel::Trace, L"BitmapScene destructor start.");
    if (_bitmap != nullptr) _bitmap->Release();
    Logger::Log(LogLevel::Trace, L"BitmapScene destructor end.");
}

void BitmapScene::Load(const D2DRenderer* renderer, const std::wstring& path)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"BitmapScene load start.");
        _path = path;
        renderer->BitmapFromFile(_path.c_str(), &_bitmap);
        Logger::Log(LogLevel::Trace, L"BitmapScene load end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"BitmapScene load fail.");
    }
}

void BitmapScene::SetCenter(const Vector& center)
{
    Logger::Log(LogLevel::Trace, L"BitmapScene set center start.");
    _center = center;
    Logger::Log(LogLevel::Trace, L"BitmapScene set center end.");
}

Vector BitmapScene::GetCenter() const
{
    return _center;
}


void BitmapScene::UpdateTransform()
{
    Logger::Log(LogLevel::Trace, L"BitmapScene update transform start.");
    const Matrix beforeInvertCenterMatrix = Matrix::Translation({
        _bitmap->GetSize().width * _center.x, _bitmap->GetSize().height * _center.y
    });
    _centerMatrix = beforeInvertCenterMatrix.Inverse();
    Scene::UpdateTransform();
    Logger::Log(LogLevel::Trace, L"BitmapScene update transform end.");
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
    if (_bitmap == nullptr) throw Exception(L"No bitmap exist, BitmapScene render fail.");
    renderer->SetTransform(_centerMatrix * _worldTransform);
    renderer->DrawBitmap(_bitmap);
    Logger::Log(LogLevel::Trace, L"BitmapScene render end.");
}
