#include "Window.h"

Window::Window(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR name, const SIZE size):
    _windowHandle(nullptr),
    _showCommand(showCommand),
    _windowClass{
        sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, DefaultWindowProcedure,
        NULL, NULL, instanceHandle, LoadIcon(instanceHandle, IDI_APPLICATION),
        LoadCursor(instanceHandle, IDC_ARROW), static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
        nullptr, name, LoadIcon(instanceHandle, IDI_APPLICATION)
    },
    _size(size)
{
}

void Window::Register() const
{
    RegisterClassEx(&_windowClass);
}

void Window::Create()
{
    RECT rect = {0, 0, _size.cx, _size.cy};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    _windowHandle = CreateWindow(_windowClass.lpszClassName, _windowClass.lpszClassName, WS_OVERLAPPEDWINDOW,
                                 rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr,
                                 _windowClass.hInstance, nullptr);
}

void Window::Show()
{
    ShowWindow(_windowHandle, _showCommand);
    UpdateWindow(_windowHandle);
}

void Window::PlaceInCenterOfScreen(const HWND windowHandle)
{
    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    RECT rect;
    GetClientRect(windowHandle, &rect);
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    const int clientWidth = rect.right - rect.left;
    const int clientHeight = rect.bottom - rect.top;
    SetWindowPos(windowHandle, nullptr, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2,
                 clientWidth, clientHeight, NULL);
}

LRESULT Window::DefaultWindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam,
                                       const LPARAM lParam)
{
    // TODO Full screen, Event programming, Extra commands
    switch (message)
    {
    case WM_CREATE:
        PlaceInCenterOfScreen(windowHandle);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
    return 0;
}
