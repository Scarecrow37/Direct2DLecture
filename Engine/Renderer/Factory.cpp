#include "pch.h"
#include "Factory.h"

Factory::Factory(const std::shared_ptr<ILoggerUnicode>& logger) : _logger(logger), _factory(nullptr)
{
    _logger->Log(LogLevel::Trace, L"Factory constructor start.");
    _logger->Log(LogLevel::Trace, L"Factory constructor end.");
}

Factory::~Factory()
{
    _logger->Log(LogLevel::Trace, L"Factory destructor start.");
    if (_factory != nullptr) _factory->Release();
    _logger->Log(LogLevel::Trace, L"Factory destructor start.");
}


void Factory::Initialize()
{
    _logger->Log(LogLevel::Trace, L"Factory initialize start.");
    // Create factory object that create Direct2D resources.
    const HRESULT resultHandle = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", Factory initialize fail."));
    _logger->Log(LogLevel::Trace, L"Factory initialize end.");
}

void Factory::CreateHwndRenderTarget(RenderTarget& renderTarget, const HWND windowHandle, const unsigned int width,
                                     const unsigned int height) const
{
    _logger->Log(LogLevel::Trace, L"Factory create window handle render target start.");
    if (_factory == nullptr) throw Exception(L"No factory exist. Factory create window handle render target fail.");
    // Create render target and set GPU resource if it support hardware acceleration.
    // It should be maintained for as long as possible.
    const D2D1_SIZE_U size = D2D1::SizeU(width, height);
    const HRESULT resultHandle = _factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                                  D2D1::HwndRenderTargetProperties(windowHandle, size),
                                                                  &renderTarget._renderTarget);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", Factory create window handle render target fail."));
    _logger->Log(LogLevel::Trace, L"Factory create window handle render target end.");
}
