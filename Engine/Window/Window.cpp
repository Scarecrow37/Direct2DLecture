#include "pch.h"
#include "Window.h"

Window::Window(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR name, const SIZE size,
               const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger),
    _windowHandle(nullptr),
    _windowClass
    {
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
    try
    {
        _logger->Log(LogLevel::Trace, L"Window initialize start.");
        Register();
        Create(AdjustWindowRect());
        Show();
        _logger->Log(LogLevel::Trace, L"Window initialize end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        throw Exception(L"Window initialize fail.");
    }
}

void Window::Finalize() const
{
    _logger->Log(LogLevel::Trace, L"Window finalize start.");
    if (_windowHandle != nullptr) DestroyWindow(_windowHandle);
    _logger->Log(LogLevel::Trace, L"Window finalize end.");
}

void Window::Register() const
{
    _logger->Log(LogLevel::Trace, L"Window register start.");
    const ATOM result = RegisterClassEx(&_windowClass);
    if (result == FALSE) throw Exception(std::to_wstring(GetLastError()).append(L", Register window class fail."));
    _logger->Log(LogLevel::Trace, L"Window register end.");
}

RECT Window::AdjustWindowRect()
{
    _logger->Log(LogLevel::Trace, L"Window adjust window rect start.");
    RECT rect = {0, 0, _size.cx, _size.cy};
    const BOOL result = ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    if (result == FALSE) throw Exception(std::to_wstring(GetLastError()).append(L", Adjust window rect fail."));
    _logger->Log(LogLevel::Trace, L"Window adjust window rect end.");
    return rect;
}

void Window::Create(const RECT windowRect)
{
    _logger->Log(LogLevel::Trace, L"Window create start.");
    _windowHandle = CreateWindow(_windowClass.lpszClassName, _windowClass.lpszClassName, WS_OVERLAPPEDWINDOW,
                                 windowRect.left, windowRect.top, windowRect.right - windowRect.left,
                                 windowRect.bottom - windowRect.top, nullptr, nullptr,
                                 _windowClass.hInstance, nullptr);
    if (_windowHandle == nullptr) throw Exception(std::to_wstring(GetLastError()).append(L", Create window fail."));
    _logger->Log(LogLevel::Trace, L"Window create end.");
}

void Window::Show()
{
    _logger->Log(LogLevel::Trace, L"Window show start.");
    if (_windowHandle == nullptr) throw Exception(L" No window handle exist. Window show fail.");
    BOOL result = ShowWindow(_windowHandle, _showCommand);
    if (result == FALSE) throw Exception(std::to_wstring(GetLastError()).append(L", Show window fail."));
    result = UpdateWindow(_windowHandle);
    if (result == FALSE) throw Exception(std::to_wstring(GetLastError()).append(L", Update window fail."));
    _logger->Log(LogLevel::Trace, L"Window show end.");
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
    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
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
