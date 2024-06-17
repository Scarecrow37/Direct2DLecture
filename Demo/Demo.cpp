#include "DemoApp.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    DemoApp app(hInstance, nShowCmd, L"Hello, World!");
    app.Initialize(false, Logger::Level::Trace);
    app.Run();
    app.Finalize();
}
