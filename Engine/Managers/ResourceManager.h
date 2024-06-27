#pragma once
#include <map>

struct IDSHAnimationAsset;

class ResourceManager
{
public:
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) noexcept = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;
    ResourceManager& operator=(ResourceManager&& other) noexcept = delete;
    ~ResourceManager();

    static void Initialize();
    static void Finalize();

    static void CreateD2D1Bitmap(const std::wstring& filePath, ID2D1Bitmap** bitmap);
    static void ReleaseD2D1Bitmap(const std::wstring& filePath);
    static void CreateDSHAnimationAsset(const std::wstring& filePath, IDSHAnimationAsset** animation);
    static void ReleaseDSHAnimationAsset(const std::wstring& filePath);

private:
    ResourceManager();
    static ResourceManager& GetInstance();

    IDSHAnimationFactory* _animationFactory;
    IWICImagingFactory* _imagingFactory;
    ID2D1HwndRenderTarget* _renderTarget;

    std::map<std::wstring, IDSHAnimationAsset*> _sharingAnimationAssets;
    std::map<std::wstring, ID2D1Bitmap*> _sharingBitmapAssets;
};
