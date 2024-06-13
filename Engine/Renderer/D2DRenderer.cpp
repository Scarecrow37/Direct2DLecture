#include "D2DRenderer.h"

#include <exception>
#include <string>

D2DRenderer::D2DRenderer(): _factory(nullptr), _renderTarget(nullptr)
{
}


void D2DRenderer::Initialize(HWND windowHandle, const unsigned int width, const unsigned int height)
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
