#include "pch.h"
#include "Frame.h"

Frame::Frame()
    : _frame(nullptr)
{
    Logger::Log(LogLevel::Trace, L"Frame constructor start.");
    Logger::Log(LogLevel::Trace, L"Frame constructor end.");
}

Frame::~Frame()
{
    Logger::Log(LogLevel::Trace, L"Frame destructor start.");
    if (_frame != nullptr) _frame->Release();
    Logger::Log(LogLevel::Trace, L"Frame destructor end.");
}
