#pragma once
#include <map>

struct ID2D1Animation;

class ResourceManager
{
public:
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) noexcept = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;
    ResourceManager& operator=(ResourceManager&& other) noexcept = delete;
    ~ResourceManager();

    static void CreateSharingAnimationAsset(const std::wstring& filePath, ID2D1Animation** animation);
    static void CreateSharingBitmapAsset(const std::wstring& filePath, ID2D1Bitmap** bitmap);
    static void ReleaseSharingAnimationAsset(const std::wstring& filePath);
    static void ReleaseSharingBitmapAsset(const std::wstring& filePath);

private:
    ResourceManager();
    static ResourceManager& GetInstance();

    std::map<std::wstring, ID2D1Animation*> _sharingAnimationAssets;
    std::map<std::wstring, ID2D1Bitmap*> _sharingBitmapAssets;
};
