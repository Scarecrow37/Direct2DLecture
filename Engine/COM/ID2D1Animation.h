#pragma once

interface ID2D1Animation abstract : IUnknown
{
    virtual ~ID2D1Animation() = default;
    virtual const std::wstring& GetBitmapFilePath() const = 0;
    virtual ID2D1Bitmap* GetBitmap() const = 0;
};
