#pragma once
#include "ID2D1Animation.h"

class D2D1Animation : public ID2D1Animation
{
public:
    D2D1Animation();
    ~D2D1Animation() override;
    HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
    ULONG AddRef() override;
    ULONG Release() override;

protected:
    std::wstring _bitmapFilePath;
    ID2D1Bitmap* _bitmap;

private:
    ULONG _refCount;
};
