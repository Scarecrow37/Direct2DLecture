#include "pch.h"
#include "DSHAnimationAsset.h"

DSHAnimationAsset::DSHAnimationAsset(): _refCount(1)
{
}

DSHAnimationAsset::DSHAnimationAsset(const std::map<std::wstring, AnimationInfo>& animations)
    : _refCount(1), _animationInfos(std::move(animations))
{
}

HRESULT DSHAnimationAsset::QueryInterface(const IID& riid, void** ppvObject)
{
    if (riid == IID_IUnknown) (*ppvObject) = static_cast<IUnknown*>(this);
    else if (riid == IID_IDSHAnimation) *ppvObject = static_cast<IDSHAnimationAsset*>(this);
    else
    {
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
}

ULONG DSHAnimationAsset::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

ULONG DSHAnimationAsset::Release()
{
    const ULONG newRefCount = InterlockedDecrement(&_refCount);
    if (newRefCount == 0) delete this;
    return newRefCount;
}

AnimationInfo* DSHAnimationAsset::GetAnimationInfo(const std::wstring& animationName)
{
    if (_animationInfos.find(animationName) == _animationInfos.end()) return nullptr;
    return &_animationInfos[animationName];
}
