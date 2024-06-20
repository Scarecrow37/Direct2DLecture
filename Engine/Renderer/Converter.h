#pragma once
#include "Frame.h"

class Converter
{
    friend class ImagingFactory;
    friend class RenderTarget;

public:
    Converter(const std::shared_ptr<ILoggerUnicode>& logger);
    Converter(const Converter& other) = default;
    Converter(Converter&& other) noexcept = default;
    Converter& operator=(const Converter& other) = default;
    Converter& operator=(Converter&& other) noexcept = default;
    ~Converter();

    void Initialize(const Frame& frame) const;

private:
    std::shared_ptr<ILoggerUnicode> _logger;

    IWICFormatConverter* _converter;
};
