#pragma once
#include "../Animation/IDSHAnimationAsset.h"


DEFINE_GUID(IID_IDSHAnimationFactory, 0x39809911, 0x87c9, 0x476f, 0xae, 0x50, 0x2a, 0x13, 0x19, 0x9b, 0x42, 0x22);
interface IDSHAnimationFactory abstract : IUnknown
{
    virtual ~IDSHAnimationFactory() = default;
    virtual HRESULT CreateAnimationFromFile(std::wstring path, IDSHAnimationAsset** animation) abstract;
};
