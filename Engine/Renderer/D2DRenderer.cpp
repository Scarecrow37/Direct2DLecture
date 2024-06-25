#include "pch.h"
#include "D2DRenderer.h"

#include "Decoder.h"
#include "Frame.h"

D2DRenderer::D2DRenderer():
    _factory(new Factory), _imagingFactory(new ImagingFactory), _renderTarget(new RenderTarget)
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer constructor start.");
    Logger::Log(LogLevel::Trace, L"D2DRenderer constructor end.");
}

D2DRenderer::~D2DRenderer()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer destructor start.");
    delete _renderTarget;
    _renderTarget = nullptr;
    delete _imagingFactory;
    _imagingFactory = nullptr;
    delete _factory;
    _factory = nullptr;
    CoUninitialize();
    Logger::Log(LogLevel::Trace, L"D2DRenderer destructor end.");
}

void D2DRenderer::Initialize(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"D2DRenderer initialize start.");
        InitializeCom();
        _factory->Initialize();
        _imagingFactory->Initialize();
        _factory->CreateHwndRenderTarget(_renderTarget, windowHandle, width, height);
        Logger::Log(LogLevel::Trace, L"D2DRenderer initialize end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"D2DRenderer initialize fail.");
    }
}

void D2DRenderer::BeginDraw() const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer begin draw start.");
    _renderTarget->BeginDraw();
    _renderTarget->ClearWhite();
    Logger::Log(LogLevel::Trace, L"D2DRenderer begin draw end.");
}

void D2DRenderer::EndDraw() const
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer end draw start.");
    _renderTarget->EndDraw();
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

void D2DRenderer::BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const
{
    // Create new IWICBitmapDecoder instance from path.
    Decoder decoder;
    _imagingFactory->CreateDecoderFromFilename(decoder, path);

    // Get frame of image.
    Frame frame;
    decoder.GetFrame(0, frame);

    // Create new IWICFormatConverter instance
    Converter converter;
    _imagingFactory->CreateFormatConverter(converter);

    converter.Initialize(frame);
    _renderTarget->CreateBitmapFromWicBitmap(converter, bitmap);
}

void D2DRenderer::InitializeCom()
{
    Logger::Log(LogLevel::Trace, L"D2DRenderer COM initialize start.");
    // Initialize COM library and identify STA in current thread.
    const HRESULT resultHandle = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer COM initialize fail."));
    Logger::Log(LogLevel::Trace, L"D2DRenderer COM initialize end.");
}
