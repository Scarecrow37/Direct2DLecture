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

void BitmapScene::Initialize()
{
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

void BitmapScene::MakeColorTransparent(const D2D1_COLOR_F& color) const
{
    // ID2D1Effect* pEffect = nullptr;
    // _renderTarget->CreateEffect(CLSID_D2D1ColorMatrix, &pEffect);
    //
    // if (pEffect) {
    //     D2D1_VECTOR_4F transparentColor = D2D1::Vector4F(1.0f, 0.0f, 1.0f, 1.0f); // 투명하게 만들 색상 (RGB: 255, 0, 255)
    //
    //     D2D1_MATRIX_5X4_F colorMatrix = {
    //         1, 0, 0, 0,
    //         0, 1, 0, 0,
    //         0, 0, 1, 0,
    //         -transparentColor.x, -transparentColor.y, -transparentColor.z, transparentColor.w
    //     };
    //     
    //     pEffect->SetInput(0, _bitmap);
    //     pEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, colorMatrix);
    //
    //     pRenderTarget->BeginDraw();
    //     pRenderTarget->DrawImage(pEffect);
    //     pRenderTarget->EndDraw();
    //
    //     pEffect->Release();
    // }
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
