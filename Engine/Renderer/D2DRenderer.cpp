#include "pch.h"
#include "D2DRenderer.h"

#include "../Managers/COMManager.h"

D2DRenderer::D2DRenderer()
    : _renderTarget(nullptr), _cameraMatrix(Matrix::Identity())
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer constructor start.");
    Logger::Log(LogLevel::Trace, L"D2DRenderer constructor end.");
}

D2DRenderer::~D2DRenderer()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer destructor start.");
    Logger::Log(LogLevel::Trace, L"D2DRenderer destructor end.");
}

void D2DRenderer::Initialize()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer initialize start.");
    COMManager::CreateD2DHwndRenderTarget(&_renderTarget);
    Logger::Log(LogLevel::Trace, L"D2DRenderer initialize end.");
}

void D2DRenderer::Finalize()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer finalize start.");
    COMManager::ReleaseD2DHwndRenderTarget();
    Logger::Log(LogLevel::Trace, L"D2DRenderer finalize end.");
}

void D2DRenderer::BeginDraw() const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer begin draw start.");
    _renderTarget->BeginDraw();
    _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    Logger::Log(LogLevel::Trace, L"D2DRenderer begin draw end.");
}

void D2DRenderer::EndDraw() const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer end draw start.");
    const HRESULT resultHandle = _renderTarget->EndDraw();
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", D2DRenderer end draw fail.")); // TODO Change Exception
    Logger::Log(LogLevel::Trace, L"D2DRenderer end draw end.");
}

void D2DRenderer::SetTransform(const D2D1_MATRIX_3X2_F& transform) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer set transform start.");
    _renderTarget->SetTransform(transform);
    Logger::Log(LogLevel::Trace, L"D2DRenderer set transform end.");
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw bitmap start.");
    _renderTarget->DrawBitmap(bitmap);
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw bitmap end.");
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap, const Rect& destinationRect, const Rect& sourceRect) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw bitmap start.");
    _renderTarget->DrawBitmap(bitmap, destinationRect, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw bitmap end.");
}

const Matrix& D2DRenderer::GetCameraMatrix() const
{
    return _cameraMatrix;
}
