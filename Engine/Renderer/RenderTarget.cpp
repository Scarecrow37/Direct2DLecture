#include "pch.h"
#include "RenderTarget.h"

#include "Converter.h"

RenderTarget::RenderTarget(const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger), _renderTarget(nullptr)
{
    _logger->Log(LogLevel::Trace, L"RenderTarget constructor start.");
    _logger->Log(LogLevel::Trace, L"RenderTarget constructor end.");
}

RenderTarget::~RenderTarget()
{
    _logger->Log(LogLevel::Trace, L"RenderTarget destructor start.");
    if (_renderTarget != nullptr) _renderTarget->Release();
    _logger->Log(LogLevel::Trace, L"RenderTarget destructor end.");
}

void RenderTarget::BeginDraw() const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget begin draw start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget begin draw fail.");
    _renderTarget->BeginDraw();
    _logger->Log(LogLevel::Trace, L"RenderTarget begin draw end.");
}

void RenderTarget::EndDraw() const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget end draw start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget end draw fail.");
    const HRESULT resultHandle = _renderTarget->EndDraw();
    if (resultHandle != S_OK)
        throw
            Exception(std::to_wstring(resultHandle).append(L", RenderTarget end draw is fail."));
    _logger->Log(LogLevel::Trace, L"RenderTarget end draw end.");
}

void RenderTarget::ClearWhite() const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget clear white start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget clear white fail.");
    _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    _logger->Log(LogLevel::Trace, L"RenderTarget clear white end.");
}

void RenderTarget::SetTransform(const D2D1_MATRIX_3X2_F& transform) const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget set transform start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget set transform fail.");
    _renderTarget->SetTransform(transform);
    _logger->Log(LogLevel::Trace, L"RenderTarget set transform end.");
}

void RenderTarget::DrawBitmap(ID2D1Bitmap* bitmap) const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget draw bitmap start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget draw bitmap fail.");
    _renderTarget->DrawBitmap(bitmap);
    _logger->Log(LogLevel::Trace, L"RenderTarget draw bitmap end.");
}

void RenderTarget::CreateBitmapFromWicBitmap(const Converter& converter, ID2D1Bitmap** bitmap) const
{
    _logger->Log(LogLevel::Trace, L"RenderTarget create bitmap from wic bitmap start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. RenderTarget create bitmap from wic bitmap fail.");
    HRESULT resultHandle = _renderTarget->CreateBitmapFromWicBitmap(converter._converter, nullptr, bitmap);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", RenderTarget create bitmap from wic bitmap fail."));
    _logger->Log(LogLevel::Trace, L"RenderTarget create bitmap from wic bitmap end.");
}
