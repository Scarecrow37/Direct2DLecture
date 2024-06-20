#pragma once

class Window
{
public:
    Window(HINSTANCE instanceHandle, int showCommand, LPCWSTR name, SIZE size,
           const std::shared_ptr<ILoggerUnicode>& logger);
    Window(const Window& other) = default;
    Window(Window&& other) noexcept = default;
    Window& operator=(const Window& other) = default;
    Window& operator=(Window&& other) noexcept = default;
    virtual ~Window() = default;

    void Initialize();
    void Finalize() const;

    HWND GetHandle() const;
    SIZE GetSize() const;
    LONG GetWidth() const;
    LONG GetHeight() const;

protected:
    std::shared_ptr<ILoggerUnicode> _logger;

    virtual void Register() const;
    virtual RECT AdjustWindowRect();
    virtual void Create(RECT windowRect);
    virtual void Show();

    HWND _windowHandle;
    WNDCLASSEX _windowClass;
    SIZE _size;

private:
    static void PlaceInCenterOfScreen(HWND windowHandle);
    static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    int _showCommand;
};
