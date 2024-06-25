#include "pch.h"
#include "ResourceManager.h"

ResourceManager::~ResourceManager()
{
    Logger::Log(LogLevel::Trace, L"ResourceManager destructor start.");
    assert(_sharingAnimationAssets.empty());
    assert(_sharingBitmapAssets.empty());
    Logger::Log(LogLevel::Trace, L"ResourceManager destructor end.");
}

void ResourceManager::CreateSharingAnimationAsset(const std::wstring& filePath, ID2D1Animation** animation)
{
}

void ResourceManager::CreateSharingBitmapAsset(const std::wstring& filePath, ID2D1Bitmap** bitmap)
{
    Logger::Log(LogLevel::Trace, L"ResourceManager create sharing bitmap asset start.");
    auto& bitmaps = GetInstance()._sharingBitmapAssets;
    if (bitmaps.find(filePath) != bitmaps.end())
    {
        *bitmap = bitmaps[filePath];
        (*bitmap)->AddRef();
    } else
    {
    }

    
}

void ResourceManager::ReleaseSharingAnimationAsset(const std::wstring& filePath)
{
}

void ResourceManager::ReleaseSharingBitmapAsset(const std::wstring& filePath)
{
}

ResourceManager::ResourceManager()
{
    Logger::Log(LogLevel::Trace, L"ResourceManager constructor start.");
    Logger::Log(LogLevel::Trace, L"ResourceManager constructor end.");
}

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager resourceManager;
    return resourceManager;
}
