#include "pch.h"
#include "ResourceManager.h"

#include "../COM/Animation/DSHAnimationAsset.h"
#include "../Managers/COMManager.h"

ResourceManager::~ResourceManager()
{
    Logger::Log(LogLevel::Trace, L"ResourceManager destructor start.");
    assert(_sharingAnimationAssets.empty());
    assert(_sharingBitmapAssets.empty());
    Logger::Log(LogLevel::Trace, L"ResourceManager destructor end.");
}

void ResourceManager::Initialize()
{
    Logger::Log(LogLevel::Trace, L"ResourceManager initialize start.");
    COMManager::CreateDSHAnimationFactory(&GetInstance()._animationFactory);
    COMManager::CreateWICImagingFactory(&GetInstance()._imagingFactory);
    COMManager::CreateD2DHwndRenderTarget(&GetInstance()._renderTarget);
    Logger::Log(LogLevel::Trace, L"ResourceManager initialize end.");
}

void ResourceManager::Finalize()
{
    Logger::Log(LogLevel::Trace, L"ResourceManager finalize start.");
    COMManager::ReleaseDSHAnimationFactory();
    COMManager::ReleaseD2DHwndRenderTarget();
    COMManager::ReleaseWICImagingFactory();
    Logger::Log(LogLevel::Trace, L"ResourceManager finalize end.");
}


void ResourceManager::CreateD2D1Bitmap(const std::wstring& filePath, ID2D1Bitmap** bitmap)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager create sharing bitmap asset start.");
    auto& resourceManager = GetInstance();
    auto& bitmaps = resourceManager._sharingBitmapAssets;
    if (bitmaps.find(filePath) == bitmaps.end())
    {
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frame = nullptr;
        IWICFormatConverter* converter = nullptr;
        HRESULT resultHandle = resourceManager._imagingFactory->CreateDecoderFromFilename(
            filePath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Create decoder from filename fail."));
        resultHandle = decoder->GetFrame(0, &frame);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Get frame fail."));
        resultHandle = resourceManager._imagingFactory->CreateFormatConverter(&converter);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Create format converter fail."));
        resultHandle = converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr,
                                             0.0f, WICBitmapPaletteTypeMedianCut);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Initialize converter fail."));
        resultHandle = resourceManager._renderTarget->CreateBitmapFromWicBitmap(converter, &bitmaps[filePath]);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Create bitmap from WIC bitmap fail."));
        converter->Release();
        frame->Release();
        decoder->Release();
    }
    else bitmaps[filePath]->AddRef();
    *bitmap = bitmaps[filePath];
    Logger::Log(LogLevel::Trace, L"ResourceManager create sharing bitmap asset end.");
}

void ResourceManager::ReleaseD2D1Bitmap(const std::wstring& filePath)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager release sharing bitmap asset start.");
    auto& bitmaps = GetInstance()._sharingBitmapAssets;
    if (bitmaps.find(filePath) == bitmaps.end()) throw Exception(L"Bitmap is not exist.");
    if (bitmaps[filePath]->Release() == 0) bitmaps.erase(filePath);
    Logger::Log(LogLevel::Trace, L"ResourceManager release sharing bitmap asset end.");
}

void ResourceManager::CreateDSHAnimationAsset(const std::wstring& filePath, IDSHAnimationAsset** animation)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager create sharing animation asset start.");
    auto& resourceManager = GetInstance();
    auto& animations = resourceManager._sharingAnimationAssets;
    if (animations.find(filePath) == animations.end())
    {
        const HRESULT resultHandle = resourceManager._animationFactory->CreateAnimationFromFile(
            filePath.c_str(), &animations[filePath]);
        if (resultHandle != S_OK)
            throw Exception(std::to_wstring(resultHandle).append(L", Create animation from file fail."));
    }
    else animations[filePath]->AddRef();
    *animation = animations[filePath];
    Logger::Log(LogLevel::Trace, L"ResourceManager create sharing animation asset end.");
}

void ResourceManager::ReleaseDSHAnimationAsset(const std::wstring& filePath)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager release sharing animation asset start.");
    auto& animations = GetInstance()._sharingAnimationAssets;
    if (animations.find(filePath) == animations.end()) throw Exception(L"Animation is not exist.");
    if (animations[filePath]->Release() == 0) animations.erase(filePath);
    Logger::Log(LogLevel::Trace, L"ResourceManager release sharing animation asset end.");
}

ResourceManager::ResourceManager(): _imagingFactory(nullptr), _renderTarget(nullptr)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager constructor start.");
    Logger::Log(LogLevel::Trace, L"ResourceManager constructor end.");
}

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager resourceManager;
    return resourceManager;
}
