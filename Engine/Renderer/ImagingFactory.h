#pragma once
#include "Converter.h"

class ImagingFactory
{
public:
    explicit ImagingFactory();
    ImagingFactory(const ImagingFactory& other) = default;
    ImagingFactory(ImagingFactory&& other) noexcept = default;
    ImagingFactory& operator=(const ImagingFactory& other) = default;
    ImagingFactory& operator=(ImagingFactory&& other) noexcept = default;
    ~ImagingFactory();

    void Initialize();

    void CreateDecoderFromFilename(Decoder& decoder, const wchar_t* path) const;
    void CreateFormatConverter(Converter& converter) const;

private:
    IWICImagingFactory* _imagingFactory;
};
