#pragma once

class Frame;

class Decoder
{
    friend class ImagingFactory;

public:
    Decoder(const std::shared_ptr<ILoggerUnicode>& logger);
    Decoder(const Decoder& other) = default;
    Decoder(Decoder&& other) noexcept = default;
    Decoder& operator=(const Decoder& other) = default;
    Decoder& operator=(Decoder&& other) noexcept = default;
    ~Decoder();

    void GetFrame(UINT index, Frame& frame) const;

private:
    std::shared_ptr<ILoggerUnicode> _logger;

    IWICBitmapDecoder* _decoder;
};
