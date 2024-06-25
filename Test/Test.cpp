#include "pch.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    GameApp gameApp(hInstance, nShowCmd, L"Hello, World!");
    gameApp.Initialize();
    gameApp.Run();
}
