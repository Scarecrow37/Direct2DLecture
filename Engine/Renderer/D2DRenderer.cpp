#include "pch.h"
#include "D2DRenderer.h"

#include "../Managers/COMManager.h"

D2DRenderer::D2DRenderer()
    : _renderTarget(nullptr), _dxgiAdapter(nullptr), _dWriteFactory(nullptr), _cameraMatrix(Matrix::Identity())
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
    COMManager::CreateDXGIAdapter(&_dxgiAdapter);
    COMManager::CreateDWriteFactory(&_dWriteFactory);
    Logger::Log(LogLevel::Trace, L"D2DRenderer initialize end.");
}

void D2DRenderer::Finalize()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer finalize start.");
    COMManager::ReleaseD2DHwndRenderTarget();
    COMManager::ReleaseDXGIAdapter();
    COMManager::ReleaseDWriteFactory();
    Logger::Log(LogLevel::Trace, L"D2DRenderer finalize end.");
}

void D2DRenderer::SetCameraMatrix(const Matrix& cameraMatrix)
{
    _cameraMatrix = cameraMatrix;
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

void D2DRenderer::DrawTextW(const std::wstring& text, const float fontSize, const Rect& destinationRect,
                            const D2D1_COLOR_F color,
                            const std::wstring& fontFamily, const DWRITE_FONT_WEIGHT weight,
                            const DWRITE_FONT_STYLE style,
                            const DWRITE_FONT_STRETCH stretch) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw text start.");
    std::wstring errorMessage{};
    IDWriteTextFormat* format = nullptr;
    ID2D1SolidColorBrush* brush = nullptr;
    HRESULT resultHandle = _dWriteFactory->CreateTextFormat(fontFamily.c_str(), nullptr, weight, style, stretch,
                                                            fontSize, L"", &format);
    if (resultHandle == S_OK) resultHandle = _renderTarget->CreateSolidColorBrush(color, &brush);
    else if (errorMessage.empty()) errorMessage = std::to_wstring(resultHandle).append(L", Create format fail.");
    if (resultHandle == S_OK) _renderTarget->DrawTextW(text.c_str(), text.length(), format, destinationRect, brush);
    else if (errorMessage.empty()) errorMessage = std::to_wstring(resultHandle).append(L", Create brush fail.");
    if (brush != nullptr) brush->Release();
    if (format != nullptr) format->Release();
    if (resultHandle != S_OK) throw Exception(std::to_wstring(resultHandle).append(errorMessage));
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw text end.");
}

void D2DRenderer::DrawRectangle(const Rect& rect, const D2D1_COLOR_F color) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw rectangle start.");
    std::wstring errorMessage{};
    ID2D1SolidColorBrush* brush = nullptr;
    const HRESULT resultHandle = _renderTarget->CreateSolidColorBrush(color, &brush);
    if (resultHandle != S_OK) errorMessage = std::to_wstring(resultHandle).append(L", Create brush fail.");
    if (resultHandle == S_OK) _renderTarget->DrawRectangle(rect, brush);
    if (brush != nullptr) brush->Release();
    if (resultHandle != S_OK) throw Exception(std::to_wstring(resultHandle).append(errorMessage));
    Logger::Log(LogLevel::Trace, L"D2DRenderer draw rectangle end.");
}

void D2DRenderer::FillRectangle(const Rect& rect, const D2D1_COLOR_F color) const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer fill rectangle start.");
    std::wstring errorMessage{};
    ID2D1SolidColorBrush* brush = nullptr;
    const HRESULT resultHandle = _renderTarget->CreateSolidColorBrush(color, &brush);
    if (resultHandle != S_OK) errorMessage = std::to_wstring(resultHandle).append(L", Create brush fail.");
    if (resultHandle == S_OK) _renderTarget->FillRectangle(rect, brush);
    if (brush != nullptr) brush->Release();
    if (resultHandle != S_OK) throw Exception(std::to_wstring(resultHandle).append(errorMessage));
    Logger::Log(LogLevel::Trace, L"D2DRenderer fill rectangle end.");
}

const Matrix& D2DRenderer::GetCameraMatrix() const
{
    return _cameraMatrix;
}

size_t D2DRenderer::GetUsedVRAM() const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer get used VRAM start.");
    DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
    const HRESULT resultHandle = _dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL,
                                                                    &videoMemoryInfo);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", D2DRenderer get used VRAM fail."));
    Logger::Log(LogLevel::Trace, L"D2DRenderer get used VRAM end.");
    return videoMemoryInfo.CurrentUsage / 1024;
}
