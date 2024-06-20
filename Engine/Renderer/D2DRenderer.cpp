#include "pch.h"
#include "D2DRenderer.h"

#include "Decoder.h"
#include "Frame.h"

D2DRenderer::D2DRenderer(const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger), _factory(logger), _imagingFactory(logger), _renderTarget(logger)
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer constructor start.");
    _logger->Log(LogLevel::Trace, L"D2DRenderer constructor end.");
}

D2DRenderer::~D2DRenderer()
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer destructor start.");
    CoUninitialize();
    _logger->Log(LogLevel::Trace, L"D2DRenderer destructor end.");
}

void D2DRenderer::Initialize(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    try
    {
        _logger->Log(LogLevel::Trace, L"D2DRenderer initialize start.");
        InitializeCom();
        _factory.Initialize();
        _imagingFactory.Initialize();
        _factory.CreateHwndRenderTarget(_renderTarget, windowHandle, width, height);
        _logger->Log(LogLevel::Trace, L"D2DRenderer initialize end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"D2DRenderer initialize fail.");
    }
}

void D2DRenderer::BeginDraw() const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer begin draw start.");
    _renderTarget.BeginDraw();
    _renderTarget.ClearWhite();
    _logger->Log(LogLevel::Trace, L"D2DRenderer begin draw end.");
}

void D2DRenderer::EndDraw() const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer end draw start.");
    _renderTarget.EndDraw();
    _logger->Log(LogLevel::Trace, L"D2DRenderer end draw end.");
}

void D2DRenderer::SetTransform(const D2D1_MATRIX_3X2_F& transform) const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer set transform start.");
    _renderTarget.SetTransform(transform);
    _logger->Log(LogLevel::Trace, L"D2DRenderer set transform end.");
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap) const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer draw bitmap start.");
    _renderTarget.DrawBitmap(bitmap);
    _logger->Log(LogLevel::Trace, L"D2DRenderer draw bitmap end.");
}

void D2DRenderer::BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const
{
    // Create new IWICBitmapDecoder instance from path.
    Decoder decoder(_logger);
    _imagingFactory.CreateDecoderFromFilename(decoder, path);

    // Get frame of image.
    Frame frame(_logger);
    decoder.GetFrame(0, frame);

    // Create new IWICFormatConverter instance
    Converter converter(_logger);
    _imagingFactory.CreateFormatConverter(converter);

    converter.Initialize(frame);
    _renderTarget.CreateBitmapFromWicBitmap(converter, bitmap);
}

void D2DRenderer::InitializeCom()
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer COM initialize start.");
    // Initialize COM library and identify STA in current thread.
    const HRESULT resultHandle = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer COM initialize fail."));
    _logger->Log(LogLevel::Trace, L"D2DRenderer COM initialize end.");
}
