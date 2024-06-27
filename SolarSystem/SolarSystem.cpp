#include "pch.h"
#include "SolarSystemApp.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    SolarSystemApp app(hInstance, nShowCmd, L"Solar System");
    app.Initialize();
    app.Run();
}