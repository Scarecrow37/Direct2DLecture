#pragma once

DEFINE_GUID(IID_IDSHAnimation, 0xefd45e35, 0x27b7, 0x4212, 0xa8, 0xa1, 0x18, 0x14, 0xfd, 0xc1, 0xa6, 0x3a);
interface IDSHAnimationAsset abstract : IUnknown
{
    virtual ~IDSHAnimationAsset() = default;
    virtual AnimationInfo* GetAnimationInfo(size_t index) abstract;
    virtual AnimationInfo* GetAnimationInfo(const std::wstring& animationName) abstract;
};
