#pragma once
#include "Frame.h"

class Converter
{
    friend class ImagingFactory;
    friend class RenderTarget;

public:
    Converter();
    Converter(const Converter& other) = default;
    Converter(Converter&& other) noexcept = default;
    Converter& operator=(const Converter& other) = default;
    Converter& operator=(Converter&& other) noexcept = default;
    ~Converter();

    void Initialize(const Frame& frame) const;

private:
    IWICFormatConverter* _converter;
};
