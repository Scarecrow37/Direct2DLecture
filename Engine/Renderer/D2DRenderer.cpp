#include "pch.h"
#include "D2DRenderer.h"

#include <exception>
#include <string>


D2DRenderer::D2DRenderer(const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger), _factory(nullptr), _imageFactory(nullptr), _renderTarget(nullptr)
{
}

void D2DRenderer::Initialize(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    try
    {
        _logger->Log(LogLevel::Trace, L"D2DRenderer initialize start.");
        InitializeCom();
        CreateFactory();
        CreateImagingFactory();
        CreateRenderTarget(windowHandle, width, height);
        _logger->Log(LogLevel::Trace, L"D2DRenderer initialize end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"D2DRenderer initialize fail.");
    }
}

void D2DRenderer::Finalize() const
{
    if (_renderTarget != nullptr) _renderTarget->Release();
    if (_imageFactory != nullptr) _imageFactory->Release();
    if (_factory != nullptr) _factory->Release();
    CoUninitialize();
}

void D2DRenderer::BeginDraw() const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer begin draw start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. D2DRenderer begin draw fail.");
    _renderTarget->BeginDraw();
    _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    _logger->Log(LogLevel::Trace, L"D2DRenderer begin draw end.");
}

void D2DRenderer::EndDraw() const
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer end draw start.");
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. D2DRenderer end draw fail.");
    const HRESULT resultHandle = _renderTarget->EndDraw();
    if (resultHandle != S_OK) throw Exception(std::to_wstring(resultHandle).append(L", End draw is fail."));
    _logger->Log(LogLevel::Trace, L"D2DRenderer end draw end.");
}

void D2DRenderer::SetTransform(const D2D1_MATRIX_3X2_F& transform) const
{
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. D2DRenderer set transform fail.");
    _renderTarget->SetTransform(transform);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap) const
{
    if (_renderTarget == nullptr) throw Exception(L"No render target exist. D2DRenderer draw bitmap fail.");
    _renderTarget->DrawBitmap(bitmap);
}

void D2DRenderer::BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const
{
    // Create new IWICBitmapDecoder instance from path. 
    IWICBitmapDecoder* decoder = nullptr;
    HRESULT resultHandle = _imageFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
                                                                    WICDecodeMetadataCacheOnDemand, &decoder);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Create decoder fail.").c_str());

    // Get frame of image.
    IWICBitmapFrameDecode* frame = nullptr;
    resultHandle = decoder->GetFrame(0, &frame);
    if (resultHandle != S_OK) throw std::exception(std::to_string(resultHandle).append(", Create frame fail.").c_str());

    // Create new IWICFormatConverter instance
    IWICFormatConverter* converter = nullptr;
    resultHandle = _imageFactory->CreateFormatConverter(&converter);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Create converter fail.").c_str());

    resultHandle = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f,
                                         WICBitmapPaletteTypeCustom);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Converter initialize fail.").c_str());

    resultHandle = _renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, bitmap);
    if (resultHandle != S_OK)
        throw
            std::exception(std::to_string(resultHandle).append(", Create bitmap fail.").c_str());

    converter->Release();
    decoder->Release();
    frame->Release();
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

void D2DRenderer::CreateFactory()
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer create factory start.");
    // Create factory object that create Direct2D resources.
    const HRESULT resultHandle = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer create factory fail."));
    _logger->Log(LogLevel::Trace, L"D2DRenderer create factory end.");
}

void D2DRenderer::CreateImagingFactory()
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer create imaging factory start.");
    // Create and initialize single object of class connected that the CLSID.
    // CLSID is static unique identifier of COM class object.
    // CLSCTX is executable context
    const HRESULT resultHandle = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                                  IID_PPV_ARGS(&_imageFactory));
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer create imaging factory fail."));
    _logger->Log(LogLevel::Trace, L"D2DRenderer create imaging factory end.");
}

void D2DRenderer::CreateRenderTarget(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    _logger->Log(LogLevel::Trace, L"D2DRenderer create render target start.");
    // Create render target and set GPU resource if it support hardware acceleration.
    // It should be maintained for as long as possible.
    const D2D1_SIZE_U size = D2D1::SizeU(width, height);
    const HRESULT resultHandle = _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                                  D2D1::HwndRenderTargetProperties(windowHandle, size),
                                                                  &_renderTarget);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer create render target fail."));
    _logger->Log(LogLevel::Trace, L"D2DRenderer create render target end.");
}
