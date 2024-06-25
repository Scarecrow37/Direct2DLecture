#pragma once

class Frame
{
    friend class Decoder;
    friend class Converter;

public:
    Frame();
    Frame(const Frame& other) = default;
    Frame(Frame&& other) noexcept = default;
    Frame& operator=(const Frame& other) = default;
    Frame& operator=(Frame&& other) noexcept = default;
    ~Frame();

private:
    IWICBitmapFrameDecode* _frame;
};
