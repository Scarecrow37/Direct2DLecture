#pragma once

class Frame
{
    friend class Decoder;
    friend class Converter;

public:
    Frame(const std::shared_ptr<ILoggerUnicode>& logger);
    Frame(const Frame& other) = default;
    Frame(Frame&& other) noexcept = default;
    Frame& operator=(const Frame& other) = default;
    Frame& operator=(Frame&& other) noexcept = default;
    ~Frame();

private:
    std::shared_ptr<ILoggerUnicode> _logger;
    
    IWICBitmapFrameDecode* _frame;
};
