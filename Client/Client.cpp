#include "pch.h"
#include "ClientApp.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    Logger::SetLeastLoglevel(LogLevel::Warning);
    ClientApp app(hInstance, nShowCmd, L"Client");
    app.Initialize();
    app.Run();
}
