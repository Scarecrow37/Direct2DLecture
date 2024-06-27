#pragma once
#include "IDSHAnimationFactory.h"

struct AnimationInfo;

class DSHAnimationFactory : public IDSHAnimationFactory
{
public:
    DSHAnimationFactory();
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

    HRESULT CreateAnimationFromFile(std::wstring path, IDSHAnimationAsset** animation) override;

private:
    static HRESULT LoadFrameFromFile(std::wstring path, AnimationInfo* animationInfo);
    
    ULONG _refCount;
};
