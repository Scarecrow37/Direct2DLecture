#include "pch.h"
#include "ImagingFactory.h"
#include "Decoder.h"

ImagingFactory::ImagingFactory()
    : _imagingFactory(nullptr)
{
    Logger::Log(LogLevel::Trace, L"ImagingFactory constructor start.");
    Logger::Log(LogLevel::Trace, L"ImagingFactory constructor end.");
}

ImagingFactory::~ImagingFactory()
{
    Logger::Log(LogLevel::Trace, L"ImagingFactory destructor start.");
    if (_imagingFactory != nullptr) _imagingFactory->Release();
    Logger::Log(LogLevel::Trace, L"ImagingFactory destructor start.");
}

void ImagingFactory::Initialize()
{
    Logger::Log(LogLevel::Trace, L"ImagingFactory initialize start.");
    // Create and initialize single object of class connected that the CLSID.
    // CLSID is static unique identifier of COM class object.
    // CLSCTX is executable context
    const HRESULT resultHandle = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                                  IID_PPV_ARGS(&_imagingFactory));
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory initialize fail."));
    Logger::Log(LogLevel::Trace, L"ImagingFactory initialize end.");
}

void ImagingFactory::CreateDecoderFromFilename(Decoder& decoder, const wchar_t* path) const
{
    Logger::Log(LogLevel::Trace, L"ImagingFactory create decoder from filename start.");
    if (_imagingFactory == nullptr)
        throw Exception(L"No imaging factory exist, ImagingFactory create decoder from filename fail.");
    const HRESULT resultHandle = _imagingFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
                                                                            WICDecodeMetadataCacheOnDemand,
                                                                            &decoder._decoder);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory create decoder fail."));
    Logger::Log(LogLevel::Trace, L"ImagingFactory create decoder from filename end.");
}

void ImagingFactory::CreateFormatConverter(Converter& converter) const
{
    Logger::Log(LogLevel::Trace, L"ImagingFactory create format converter start.");
    if (_imagingFactory == nullptr)
        throw Exception(L"No imaging factory exist, ImagingFactory create format converter fail.");
    const HRESULT resultHandle = _imagingFactory->CreateFormatConverter(&converter._converter);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory create format converter fail."));
    Logger::Log(LogLevel::Trace, L"ImagingFactory create format converter end.");
}


