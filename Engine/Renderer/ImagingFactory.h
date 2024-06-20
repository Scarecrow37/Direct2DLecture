#pragma once
#include "Converter.h"
#include "Decoder.h"

class ImagingFactory
{
public:
    explicit ImagingFactory(const std::shared_ptr<ILoggerUnicode>& logger);
    ImagingFactory(const ImagingFactory& other) = default;
    ImagingFactory(ImagingFactory&& other) noexcept = default;
    ImagingFactory& operator=(const ImagingFactory& other) = default;
    ImagingFactory& operator=(ImagingFactory&& other) noexcept = default;
    ~ImagingFactory();

    void Initialize();

    void CreateDecoderFromFilename(Decoder& decoder, const wchar_t* path) const;
    void CreateFormatConverter(Converter& converter) const;

private:
    std::shared_ptr<ILoggerUnicode> _logger;

    IWICImagingFactory* _imagingFactory;
};
