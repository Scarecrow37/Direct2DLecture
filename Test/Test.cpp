#include "pch.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    const std::shared_ptr<ILoggerUnicode> logger = std::make_shared<ConsoleLoggerUnicode>();
    GameApp gameApp(hInstance, nShowCmd, L"Hello, World!", logger);
    gameApp.Initialize();
    gameApp.Run();
}
