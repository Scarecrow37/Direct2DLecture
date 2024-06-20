#include "pch.h"
#include "Converter.h"

Converter::Converter(const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger), _converter(nullptr)
{
    _logger->Log(LogLevel::Trace, L"Converter constructor start.");
    _logger->Log(LogLevel::Trace, L"Converter constructor end.");
}

Converter::~Converter()
{
    _logger->Log(LogLevel::Trace, L"Converter destructor start.");
    if (_converter != nullptr) _converter->Release();
    _logger->Log(LogLevel::Trace, L"Converter destructor end.");
}

void Converter::Initialize(const Frame& frame) const
{
    _logger->Log(LogLevel::Trace, L"Converter initialize start.");
    if (_converter == nullptr)
    throw Exception(L"No converter exist. Converter initialize fail.");
    HRESULT resultHandle = _converter->Initialize(frame._frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f,
                           WICBitmapPaletteTypeCustom);
    if (resultHandle != S_OK)
        throw   Exception(std::to_wstring(resultHandle).append(L", Converter initialize fail."));
    _logger->Log(LogLevel::Trace, L"Converter initialize end.");
}
