#include "ChainStreamBuffer.h"

ChainStreamBuffer::ChainStreamBuffer(std::streambuf* buffer1, std::streambuf* buffer2)
    : _buffer1(buffer1), _buffer2(buffer2)
{
}

int ChainStreamBuffer::overflow(const int_type character)
{
    if (character == EOF) return !EOF;
    const int result1 = _buffer1->sputc(static_cast<char>(character));
    // Store character at current put position and increase put position
    const int result2 = _buffer2->sputc(static_cast<char>(character));
    // Store character at current put position and increase put position
    return result1 == EOF || result2 == EOF ? EOF : character;
}

int ChainStreamBuffer::sync()
{
    const int result1 = _buffer1->pubsync(); // Synchronize stream buffer
    const int result2 = _buffer2->pubsync(); // Synchronize stream buffer
    return result1 == 0 && result2 == 0 ? 0 : -1;
}
