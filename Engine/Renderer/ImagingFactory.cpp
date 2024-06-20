#include "pch.h"
#include "ImagingFactory.h"

ImagingFactory::ImagingFactory(const std::shared_ptr<ILoggerUnicode>& logger) : _logger(logger),
    _imagingFactory(nullptr)
{
    _logger->Log(LogLevel::Trace, L"ImagingFactory constructor start.");
    _logger->Log(LogLevel::Trace, L"ImagingFactory constructor end.");
}

ImagingFactory::~ImagingFactory()
{
    _logger->Log(LogLevel::Trace, L"ImagingFactory destructor start.");
    if (_imagingFactory != nullptr) _imagingFactory->Release();
    _logger->Log(LogLevel::Trace, L"ImagingFactory destructor start.");
}

void ImagingFactory::Initialize()
{
    _logger->Log(LogLevel::Trace, L"ImagingFactory initialize start.");
    // Create and initialize single object of class connected that the CLSID.
    // CLSID is static unique identifier of COM class object.
    // CLSCTX is executable context
    const HRESULT resultHandle = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                                  IID_PPV_ARGS(&_imagingFactory));
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory initialize fail."));
    _logger->Log(LogLevel::Trace, L"ImagingFactory initialize end.");
}

void ImagingFactory::CreateDecoderFromFilename(Decoder& decoder, const wchar_t* path) const
{
    _logger->Log(LogLevel::Trace, L"ImagingFactory create decoder from filename start.");
    if (_imagingFactory == nullptr)
        throw Exception(L"No imaging factory exist, ImagingFactory create decoder from filename fail.");
    const HRESULT resultHandle = _imagingFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
                                                                            WICDecodeMetadataCacheOnDemand,
                                                                            &decoder._decoder);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory create decoder fail."));
    _logger->Log(LogLevel::Trace, L"ImagingFactory create decoder from filename end.");
}

void ImagingFactory::CreateFormatConverter(Converter& converter) const
{
    _logger->Log(LogLevel::Trace, L"ImagingFactory create format converter start.");
    if (_imagingFactory == nullptr)
        throw Exception(L"No imaging factory exist, ImagingFactory create format converter fail.");
    const HRESULT resultHandle = _imagingFactory->CreateFormatConverter(&converter._converter);
    if (resultHandle != S_OK)
        throw Exception(std::to_wstring(resultHandle).append(L", ImagingFactory create format converter fail."));
    _logger->Log(LogLevel::Trace, L"ImagingFactory create format converter end.");
}


