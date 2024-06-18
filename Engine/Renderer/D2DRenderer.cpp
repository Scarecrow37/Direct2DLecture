#include "pch.h"
#include "D2DRenderer.h"

#include <exception>
#include <string>

D2DRenderer::D2DRenderer(): _factory(nullptr), _imageFactory(nullptr), _renderTarget(nullptr)
{
}


void D2DRenderer::Initialize(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    // Initialize COM library and identify STA in current thread.
    HRESULT resultHandle = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", COM initialize fail.").c_str());

    // Create factory object that create Direct2D resources.
    resultHandle = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Create factory fail.").c_str());

    // Create and initialize single object of class connected that the CLSID.
    // CLSID is static unique identifier of COM class object.
    // CLSCTX is executable context
    resultHandle = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                    IID_PPV_ARGS(&_imageFactory));
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Create imaging factory fail.").c_str());

    // Create render target and set GPU resource if it support hardware acceleration.
    // It should be maintained for as long as possible.
    const D2D1_SIZE_U size = D2D1::SizeU(width, height);
    resultHandle = _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                    D2D1::HwndRenderTargetProperties(windowHandle, size),
                                                    &_renderTarget);
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", Create factory fail.").c_str());
}

void D2DRenderer::Finalize()
{
    _renderTarget->Release();
    _factory->Release();
    CoUninitialize();
}

void D2DRenderer::BeginDraw() const
{
    _renderTarget->BeginDraw();
    _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void D2DRenderer::EndDraw() const
{
    const HRESULT resultHandle = _renderTarget->EndDraw();
    if (resultHandle != S_OK)
        throw std::exception(
            std::to_string(resultHandle).append(", End draw is fail.").c_str());
}

void D2DRenderer::SetTransform(const D2D1_MATRIX_3X2_F& transform) const
{
    _renderTarget->SetTransform(transform);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap* bitmap) const
{
    _renderTarget->DrawBitmap(bitmap);
}

void D2DRenderer::BitmapFromFile(const wchar_t* path, ID2D1Bitmap** bitmap) const
{
    // Create new IWICBitmapDecoder instance from path. 
    IWICBitmapDecoder* decoder = nullptr;
    HRESULT resultHandle = _imageFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
                                                                    WICDecodeMetadataCacheOnDemand, &decoder);
    if (resultHandle != S_OK) throw std::exception( std::to_string(resultHandle).append(", Create decoder fail.").c_str());

    // Get frame of image.
    IWICBitmapFrameDecode* frame = nullptr;
    resultHandle = decoder->GetFrame(0, &frame);
    if (resultHandle != S_OK) throw std::exception( std::to_string(resultHandle).append(", Create frame fail.").c_str());

    // Create new IWICFormatConverter instance
    IWICFormatConverter* converter = nullptr;
    resultHandle = _imageFactory->CreateFormatConverter(&converter);
    if (resultHandle != S_OK) throw std::exception( std::to_string(resultHandle).append(", Create converter fail.").c_str());
    
    resultHandle = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
    if (resultHandle != S_OK) throw std::exception( std::to_string(resultHandle).append(", Converter initialize fail.").c_str());

    resultHandle = _renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, bitmap);
    if (resultHandle != S_OK) throw std::exception( std::to_string(resultHandle).append(", Create bitmap fail.").c_str());

    converter->Release();
    decoder->Release();
    frame->Release();
}
