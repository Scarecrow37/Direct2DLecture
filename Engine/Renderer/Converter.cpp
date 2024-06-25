#include "pch.h"
#include "Converter.h"

Converter::Converter()
    : _converter(nullptr)
{
    Logger::Log(LogLevel::Trace, L"Converter constructor start.");
    Logger::Log(LogLevel::Trace, L"Converter constructor end.");
}

Converter::~Converter()
{
    Logger::Log(LogLevel::Trace, L"Converter destructor start.");
    if (_converter != nullptr) _converter->Release();
    Logger::Log(LogLevel::Trace, L"Converter destructor end.");
}

void Converter::Initialize(const Frame& frame) const
{
    Logger::Log(LogLevel::Trace, L"Converter initialize start.");
    if (_converter == nullptr)
        throw Exception(L"No converter exist. Converter initialize fail.");
    HRESULT resultHandle = _converter->Initialize(frame._frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
                                                  nullptr, 0.f,
                                                  WICBitmapPaletteTypeCustom);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", Converter initialize fail."));
    Logger::Log(LogLevel::Trace, L"Converter initialize end.");
}
