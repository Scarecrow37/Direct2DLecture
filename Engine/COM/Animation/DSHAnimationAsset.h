#pragma once
#include "IDSHAnimationAsset.h"

class DSHAnimationAsset : public IDSHAnimationAsset
{
public:
    DSHAnimationAsset();
    DSHAnimationAsset(const std::vector<AnimationInfo>& animations);
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

    AnimationInfo* GetAnimationInfo(size_t index) override;
    AnimationInfo* GetAnimationInfo(const std::wstring& animationName) override;

private:
    ULONG _refCount;
    std::wstring _path;

    std::vector<AnimationInfo> _animationInfos;
};
