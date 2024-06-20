#include "pch.h"
#include "Frame.h"

Frame::Frame(const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger), _frame(nullptr)
{
    _logger->Log(LogLevel::Trace, L"Frame constructor start.");
    _logger->Log(LogLevel::Trace, L"Frame constructor end.");
}

Frame::~Frame()
{
    _logger->Log(LogLevel::Trace, L"Frame destructor start.");
    if (_frame != nullptr) _frame->Release();
    _logger->Log(LogLevel::Trace, L"Frame destructor end.");
}
