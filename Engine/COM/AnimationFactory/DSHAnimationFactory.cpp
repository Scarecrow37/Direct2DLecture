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
    std::map<std::wstring, AnimationInfo> animationInfos;
    std::wifstream file(path);
    if (!file.is_open()) return E_INVALIDARG;
    std::wstring line;
    size_t animationCount = 0;
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        wss >> animationCount;
    }
    for (size_t i = 0; i < animationCount; ++i)
    {
        std::getline(file, line);
        std::wstringstream wss(line);
        {
            std::wstring animationFile;
            std::wstring animationName;
            std::getline(wss, animationName, L',');
            std::getline(wss, animationFile, L',');
            HRESULT result = LoadAnimationInfo(animationFile, &animationInfos[animationName]);
            if (result != S_OK) return result;
        }
    }
    *animation = new DSHAnimationAsset(animationInfos);
    return S_OK;
}

HRESULT DSHAnimationFactory::LoadAnimationInfo(std::wstring path, AnimationInfo* animationInfo)
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
        std::getline(file, line);
        std::wstringstream wss(line);
        std::wstring token;
        {
            std::getline(wss, token, L',');
            animationInfo->frames[i].source.left = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].source.top = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].source.right = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].source.bottom = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].center.x = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].center.y = static_cast<float>(_wtoi(token.c_str()));
            std::getline(wss, token, L',');
            animationInfo->frames[i].duration = static_cast<float>(_wtoi(token.c_str()));
        }
    }
    return S_OK;
}
