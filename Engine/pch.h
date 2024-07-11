#pragma once
#ifndef  PCH_H
#define PCH_H

#include "Framework.h"
#include <memory>
#include <functional>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <wrl.h>
#include <d3d11_2.h>
#include <d2d1_1.h>
#include <d2d1_2.h>
#include <d2d1_1helper.h>
#include <d2d1effects_2.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1helper.h>
#include <dxgi1_4.h>

#include "../Exception/Exception.h"
#include "../Logger/LogLevel.h"
#include "../Logger/Interfaces/ILogger.h"

#include "Logger/Logger.h"
#include "Models/Models.h"
#include "Math/Math.h"
#include "COM/COM.h"
#include "Time/Time.h"
#include "Input/Input.h"
#include "Managers/Managers.h"


namespace DX
{
    inline void ThrowIfFailed(const HRESULT hr)
    {
        if (FAILED(hr)) throw Exception(std::to_wstring(hr).append(L", DirectX error."));
    }

#if defined(_DEBUG)
    // Check for SDK Layer support.
    inline bool SdkLayersAvailable()
    {
        HRESULT hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_NULL, // There is no need to create a real hardware device.
            0,
            D3D11_CREATE_DEVICE_DEBUG, // Check for the SDK layers.
            nullptr, // Any feature level will do.
            0,
            D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for Windows Store apps.
            nullptr, // No need to keep the D3D device reference.
            nullptr, // No need to know the feature level.
            nullptr // No need to keep the D3D device context reference.
        );

        return SUCCEEDED(hr);
    }
#endif
}

#endif
