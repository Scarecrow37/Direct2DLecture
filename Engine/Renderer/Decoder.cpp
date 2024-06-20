#include "pch.h"
#include "Decoder.h"

#include "Frame.h"

Decoder::Decoder(const std::shared_ptr<ILoggerUnicode>& logger): _logger(logger), _decoder(nullptr)
{
    _logger->Log(LogLevel::Trace, L"Decoder constructor start.");
    _logger->Log(LogLevel::Trace, L"Decoder constructor end.");
}

Decoder::~Decoder()
{
    _logger->Log(LogLevel::Trace, L"Decoder destructor start.");
    if (_decoder != nullptr) _decoder->Release();
    _logger->Log(LogLevel::Trace, L"Decoder destructor end.");
}

void Decoder::GetFrame(const UINT index, Frame& frame) const
{
    _logger->Log(LogLevel::Trace, L"Decoder get frame start.");
    if (_decoder == nullptr) throw Exception(L"No decoder exist. Decoder get frame fail.");
    const HRESULT resultHandle = _decoder->GetFrame(index, &frame._frame);
    if(resultHandle != S_OK) throw Exception(std::to_wstring(resultHandle).append(L", Decoder get frame fail."));
    _logger->Log(LogLevel::Trace, L"Decoder get frame end.");
}
