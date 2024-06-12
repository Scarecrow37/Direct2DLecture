#pragma once
#include <streambuf>

class ChainStreamBuffer : public std::streambuf
{
public:
    ChainStreamBuffer(std::streambuf* buffer1, std::streambuf* buffer2);

protected:
    int overflow(const int_type character) override; // Check end of file

    int sync() override;

private:
    std::streambuf* _buffer1;
    std::streambuf* _buffer2;
};
