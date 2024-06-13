#include "Window.h"

#include <exception>
#include <string>

Window::Window(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR name, const SIZE size):
    _windowHandle(nullptr),
    _windowClass{
        sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, DefaultWindowProcedure,
        NULL, NULL, instanceHandle, LoadIcon(instanceHandle, IDI_APPLICATION),
        LoadCursor(instanceHandle, IDC_ARROW), static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
        nullptr, name, LoadIcon(instanceHandle, IDI_APPLICATION)
    },
    _size(size),
    _showCommand(showCommand)
{
}

void Window::Initialize()
{
    if (Register() == FALSE)
        throw std::exception(std::to_string(GetLastError()).append(", Register window class fail.").c_str());
    RECT rect = {0, 0, _size.cx, _size.cy};
    if (AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE) == FALSE)
        throw std::exception(std::to_string(GetLastError()).append(", Adjust window rect fail.").c_str());
    _windowHandle = Create(rect);
    if (_windowHandle == nullptr)
        throw std::exception(std::to_string(GetLastError()).append(", Create window fail.").c_str());
    Show();
}

void Window::Finalize()
{
    if (_windowHandle != nullptr) DestroyWindow(_windowHandle);
}

ATOM Window::Register() const
{
    return RegisterClassEx(&_windowClass);
}

HWND Window::Create(const RECT windowRect)
{
    return CreateWindow(_windowClass.lpszClassName, _windowClass.lpszClassName, WS_OVERLAPPEDWINDOW,
                        windowRect.left, windowRect.top, windowRect.right - windowRect.left,
                        windowRect.bottom - windowRect.top, nullptr, nullptr,
                        _windowClass.hInstance, nullptr);
}

void Window::Show()
{
    ShowWindow(_windowHandle, _showCommand);
    UpdateWindow(_windowHandle);
}

HWND Window::GetHandle() const
{
    return _windowHandle;
}

SIZE Window::GetSize() const
{
    return _size;
}

LONG Window::GetWidth() const
{
    return _size.cx;
}

LONG Window::GetHeight() const
{
    return _size.cy;
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
