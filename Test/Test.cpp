#include "../Engine/Window/Window.h"

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    Window window(hInstance, nShowCmd, L"Hello, World!", {1920, 1080});
    window.Register();
    window.Create();
    window.Show();
    while (true)
    {
    }
}
