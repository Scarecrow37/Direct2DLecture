#include "pch.h"
#include "DSHAnimationFactory.h"

#include "../Animation/DSHAnimationAsset.h"

DSHAnimationFactory::DSHAnimationFactory() : _refCount(1)
{
}

HRESULT DSHAnimationFactory::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_IDSHAnimationFactory) *ppvObject = static_cast<IDSHAnimationFactory*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG DSHAnimationFactory::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG DSHAnimationFactory::Release()
{
    ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0) delete this;
    return newRefCount;
}

HRESULT DSHAnimationFactory::CreateAnimationFromFile(const std::wstring path, IDSHAnimationAsset** animation)
{
    std::vector<AnimationInfo> animationInfos;
    std::wifstream file(path);
    if (!file.is_open()) return E_INVALIDARG;
    std::wstring line;
    size_t animationCount = 0;
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        wss >> animationCount;
    }
    animationInfos.reserve(animationCount);
    for (size_t i = 0; i < animationCount; ++i)
    {
        AnimationInfo animationInfo;
        std::getline(file, line);
        std::wstringstream wss(line);
        {
            std::wstring animationName;
            std::wstring animationLoop;
            std::wstring animationFile;
            std::getline(wss, animationName, L',');
            animationInfo.name = animationName;
            std::getline(wss, animationLoop, L',');
            animationInfo.isLoop = static_cast<bool>(std::stoi(animationLoop));
            std::getline(wss, animationFile, L',');
            HRESULT result = LoadFrameFromFile( path.substr(0, path.find_last_of(L"/\\") + 1).append(animationFile), &animationInfo);
            if (result != S_OK) return result;
        }
        animationInfos.push_back(animationInfo);
    }
    *animation = new DSHAnimationAsset(animationInfos);
    file.close();
    return S_OK;
}

HRESULT DSHAnimationFactory::LoadFrameFromFile(std::wstring path, AnimationInfo* animationInfo)
{
    std::wifstream file(path);
    if (!file.is_open()) return E_INVALIDARG;
    std::wstring line;
    size_t frameCount = 0;
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        wss >> frameCount;
    }
    animationInfo->frames.reserve(frameCount);
    for (size_t i = 0; i < frameCount; ++i)
    {
        FrameInfo frameInfo;
        std::getline(file, line);
        std::wstringstream wss(line);
        std::wstring token;
        {
            std::getline(wss, token, L',');
            frameInfo.source.left = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.source.top = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.source.right = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.source.bottom = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.center.x = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.center.y = std::stof(token);
            std::getline(wss, token, L',');
            frameInfo.duration = std::stof(token);
        }
        animationInfo->frames.push_back(frameInfo);
    }
    file.close();
    return S_OK;
}
