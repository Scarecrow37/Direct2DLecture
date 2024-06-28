#include "pch.h"
#include "COMManager.h"

#include "../COM/AnimationFactory/DSHAnimationFactory.h"

COMManager::~COMManager()
{
    Logger::Log(LogLevel::Trace, L"COMManager destructor start.");
    Logger::Log(LogLevel::Trace, L"COMManager destructor end.");
}

void COMManager::Initialize(const HWND windowHandle, const unsigned int width, const unsigned int height)
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize start.");
    InitializeCOM();
    InitializeFactory();
    InitializeImagingFactory();
    InitializeAnimationFactory();
    InitializeHwndRenderTarget(windowHandle, width, height);
    InitializeDXGIFactory();
    InitializeDXGIAdapter();
    InitializeDWriteFactory();
    Logger::Log(LogLevel::Trace, L"COMManager initialize end.");
}

void COMManager::InitializeCOM()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize COM start.");
    // Initialize COM library and identify STA in current thread.
    const HRESULT resultHandle = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", D2DRenderer COM initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize COM end.");
}

void COMManager::InitializeFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize factory start.");
    // Create factory object that create Direct2D resources.
    const HRESULT resultHandle = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &GetInstance()._factory);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", Factory initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize factory end.");
}

void COMManager::InitializeImagingFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize imaging factory start.");
    // Create and initialize single object of class connected that the CLSID.
    // CLSID is static unique identifier of COM class object.
    // CLSCTX is executable context
    const HRESULT resultHandle = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                                  IID_PPV_ARGS(&GetInstance()._imagingFactory));
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", ImagingFactory initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize imaging factory end.");
}

void COMManager::InitializeAnimationFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize animation factory start.");
    GetInstance()._animationFactory = new DSHAnimationFactory();
    Logger::Log(LogLevel::Trace, L"COMManager initialize animation factory end.");
}

void COMManager::InitializeHwndRenderTarget(const HWND windowHandle, const unsigned int width,
                                            const unsigned int height)
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize hwnd render target start.");
    // Create render target and set GPU resource if it supports hardware acceleration.
    // It should be maintained for as long as possible.
    const D2D1_SIZE_U size = D2D1::SizeU(width, height);
    const HRESULT resultHandle = GetInstance()._factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            windowHandle, size), &GetInstance()._hwndRenderTarget);
    if (resultHandle != S_OK)
        throw Exception(
            std::to_wstring(resultHandle).append(L", Factory create window handle render target fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize hwnd render target end.");
}

void COMManager::InitializeDXGIFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize DXGI factory start.");
    const HRESULT resultHandle = CreateDXGIFactory1(__uuidof(IDXGIFactory4),
                                                    reinterpret_cast<void**>(&GetInstance()._dxgiFactory));
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", DXGI Factory initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize DXGI factory end.");
}

void COMManager::InitializeDXGIAdapter()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize DXGI adapter start.");
    const HRESULT resultHandle = GetInstance()._dxgiFactory->EnumAdapters(
        0, reinterpret_cast<IDXGIAdapter**>(&GetInstance()._dxgiAdapter));
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", DXGI Adapter initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize DXGI adapter end.");
}

void COMManager::InitializeDWriteFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager initialize DWrite factory start.");
    const HRESULT resultHandle = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                                     reinterpret_cast<IUnknown**>(&GetInstance()._writeFactory));
    if (resultHandle != S_OK) throw Exception(
        std::to_wstring(resultHandle).append(L", DWrite Factory initialize fail."));
    Logger::Log(LogLevel::Trace, L"COMManager initialize DWrite factory end.");
}


void COMManager::Finalize()
{
    Logger::Log(LogLevel::Trace, L"COMManager uninitialize COM start.");
    COMManager& comManager = GetInstance();
    if (comManager._writeFactory->Release() != 0) throw Exception(L"Factory is referenced by other objects.");
    comManager._writeFactory = nullptr;
    if (comManager._dxgiAdapter->Release() != 0) throw Exception(L"Adapter is referenced by other objects.");
    comManager._dxgiAdapter = nullptr;
    if (comManager._dxgiFactory->Release() != 0) throw Exception(L"Factory is referenced by other objects.");
    comManager._dxgiFactory = nullptr;
    if (comManager._animationFactory->Release() != 0)
        throw Exception(
            L"AnimationFactory is referenced by other objects.");
    comManager._animationFactory = nullptr;
    if (comManager._imagingFactory->Release() != 0) throw Exception(L"ImagingFactory is referenced by other objects.");
    comManager._imagingFactory = nullptr;
    if (comManager._hwndRenderTarget->Release() != 0) throw Exception(L"RenderTarget is referenced by other objects.");
    comManager._hwndRenderTarget = nullptr;
    if (comManager._factory->Release() != 0) throw Exception(L"Factory is referenced by other objects.");
    comManager._factory = nullptr;
    CoUninitialize();
    Logger::Log(LogLevel::Trace, L"COMManager uninitialize COM end.");
}

void COMManager::CreateD2D1Factory(ID2D1Factory** factory)
{
    Logger::Log(LogLevel::Trace, L"COMManager create D2D1 factory start.");
    *factory = GetInstance()._factory;
    GetInstance()._factory->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create D2D1 factory end.");
}

void COMManager::ReleaseD2D1Factory()
{
    Logger::Log(LogLevel::Trace, L"COMManager release D2D1 factory start.");
    GetInstance()._factory->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release D2D1 factory end.");
}

void COMManager::CreateWICImagingFactory(IWICImagingFactory** imagingFactory)
{
    Logger::Log(LogLevel::Trace, L"COMManager create WIC imaging factory start.");
    *imagingFactory = GetInstance()._imagingFactory;
    GetInstance()._imagingFactory->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create WIC imaging factory end.");
}

void COMManager::ReleaseWICImagingFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager release WIC imaging factory start.");
    GetInstance()._imagingFactory->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release WIC imaging factory end.");
}

void COMManager::CreateD2DHwndRenderTarget(ID2D1HwndRenderTarget** hwndRenderTarget)
{
    Logger::Log(LogLevel::Trace, L"COMManager create D2D1 render target start.");
    *hwndRenderTarget = GetInstance()._hwndRenderTarget;
    GetInstance()._hwndRenderTarget->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create D2D1 render target end.");
}

void COMManager::ReleaseD2DHwndRenderTarget()
{
    Logger::Log(LogLevel::Trace, L"COMManager release D2D1 render target start.");
    GetInstance()._hwndRenderTarget->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release D2D1 render target end.");
}

void COMManager::CreateDXGIFactory(IDXGIFactory4** dxgiFactory)
{
    Logger::Log(LogLevel::Trace, L"COMManager create DXGI factory start.");
    *dxgiFactory = GetInstance()._dxgiFactory;
    GetInstance()._dxgiFactory->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create DXGI factory end.");
}

void COMManager::ReleaseDXGIFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager release DXGI factory start.");
    GetInstance()._dxgiFactory->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release DXGI factory end.");
}

void COMManager::CreateDXGIAdapter(IDXGIAdapter3** dxgiAdapter)
{
    Logger::Log(LogLevel::Trace, L"COMManager create DXGI adapter start.");
    *dxgiAdapter = GetInstance()._dxgiAdapter;
    GetInstance()._dxgiAdapter->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create DXGI adapter end.");
}

void COMManager::ReleaseDXGIAdapter()
{
    Logger::Log(LogLevel::Trace, L"COMManager release DXGI adapter start.");
    GetInstance()._dxgiAdapter->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release DXGI adapter end.");
}

void COMManager::CreateDWriteFactory(IDWriteFactory** writeFactory)
{
    Logger::Log(LogLevel::Trace, L"COMManager create DWrite factory start.");
    *writeFactory = GetInstance()._writeFactory;
    GetInstance()._writeFactory->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create DWrite factory end.");
}

void COMManager::ReleaseDWriteFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager release DWrite factory start.");
    GetInstance()._writeFactory->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release DWrite factory end.");
}


void COMManager::CreateDSHAnimationFactory(IDSHAnimationFactory** animationFactory)
{
    Logger::Log(LogLevel::Trace, L"COMManager create DSH animation factory start.");
    *animationFactory = GetInstance()._animationFactory;
    GetInstance()._animationFactory->AddRef();
    Logger::Log(LogLevel::Trace, L"COMManager create DSH animation factory end.");
}

void COMManager::ReleaseDSHAnimationFactory()
{
    Logger::Log(LogLevel::Trace, L"COMManager release DSH animation factory start.");
    GetInstance()._animationFactory->Release();
    Logger::Log(LogLevel::Trace, L"COMManager release DSH animation factory end.");
}

COMManager::COMManager()
    : _factory(nullptr), _imagingFactory(nullptr), _animationFactory(nullptr), _hwndRenderTarget(nullptr)
{
    Logger::Log(LogLevel::Trace, L"COMManager constructor start.");
    Logger::Log(LogLevel::Trace, L"COMManager constructor end.");
}

COMManager& COMManager::GetInstance()
{
    static COMManager comManager;
    return comManager;
}
