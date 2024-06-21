#include "pch.h"
#include "SolarSystemApp.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    const std::shared_ptr<ILoggerUnicode> logger = std::make_shared<ConsoleLoggerUnicode>();
    logger->SetLeastLoglevel(LogLevel::Warning);
    SolarSystemApp app(hInstance, nShowCmd, L"Solar System", logger);
    app.Initialize();
    app.Run();
}
