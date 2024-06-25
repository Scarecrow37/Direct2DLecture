#pragma once

DEFINE_GUID(IID_IAnimation, 0xefd45e35, 0x27b7, 0x4212, 0xa8, 0xa1, 0x18, 0x14, 0xfd, 0xc1, 0xa6, 0x3a);
interface ID2D1Animation abstract : IUnknown
{
    virtual ~ID2D1Animation() = default;
    virtual const std::wstring& GetBitmapFilePath() const = 0;
    virtual ID2D1Bitmap* GetBitmap() const = 0;
};
