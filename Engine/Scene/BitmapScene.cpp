#include "pch.h"
#include "BitmapScene.h"

#include "../Renderer/D2DRenderer.h"

BitmapScene::BitmapScene(const std::shared_ptr<ILoggerUnicode>& logger)
    : BitmapScene(logger, nullptr)
{
    _logger->Log(LogLevel::Trace, L"BitmapScene constructor start.");
    _logger->Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::BitmapScene(const std::shared_ptr<ILoggerUnicode>& logger, const Scene* parent)
    : Scene(logger, parent), _center(0.f, 0.f), _centerMatrix(D2D1::Matrix3x2F::Identity()), _bitmap(nullptr)
{
    _logger->Log(LogLevel::Trace, L"BitmapScene constructor start.");
    _logger->Log(LogLevel::Trace, L"BitmapScene constructor end.");
}

BitmapScene::~BitmapScene()
{
    _logger->Log(LogLevel::Trace, L"BitmapScene destructor start.");
    if (_bitmap != nullptr) _bitmap->Release();
    _logger->Log(LogLevel::Trace, L"BitmapScene destructor end.");
}

void BitmapScene::Load(const D2DRenderer& renderer, const std::wstring& path)
{
    try
    {
        _logger->Log(LogLevel::Trace, L"BitmapScene load start.");
        _path = path;
        renderer.BitmapFromFile(_path.c_str(), &_bitmap);
        _logger->Log(LogLevel::Trace, L"BitmapScene load end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"BitmapScene load fail.");
    }
}

void BitmapScene::SetCenter(const Vector& center)
{
    _logger->Log(LogLevel::Trace, L"BitmapScene set center start.");
    _center = center;
    _logger->Log(LogLevel::Trace, L"BitmapScene set center end.");
}

Vector BitmapScene::GetCenter() const
{
    return _center;
}


void BitmapScene::UpdateTransform()
{
    _logger->Log(LogLevel::Trace, L"BitmapScene update transform start.");
    const Matrix beforeInvertCenterMatrix = Matrix::Translation({
        _bitmap->GetSize().width * _center.x, _bitmap->GetSize().height * _center.y
    });
    _centerMatrix = beforeInvertCenterMatrix.Inverse();
    Scene::UpdateTransform();
    _logger->Log(LogLevel::Trace, L"BitmapScene update transform end.");
}

void BitmapScene::Update(const float deltaTime)
{
    _logger->Log(LogLevel::Trace, L"BitmapScene update start.");
    UpdateTransform();
    _logger->Log(LogLevel::Trace, L"BitmapScene update end.");
}

void BitmapScene::Render(const D2DRenderer& renderer) const
{
    _logger->Log(LogLevel::Trace, L"BitmapScene render start.");
    if (_bitmap == nullptr) throw Exception(L"No bitmap exist, BitmapScene render fail.");
    renderer.SetTransform(_centerMatrix * _worldTransform);
    renderer.DrawBitmap(_bitmap);
    _logger->Log(LogLevel::Trace, L"BitmapScene render end.");
}
