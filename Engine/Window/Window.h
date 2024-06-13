#pragma once
#include "../Framework.h"

class Window
{
public:
    Window(HINSTANCE instanceHandle, int showCommand, LPCWSTR name, SIZE size);
    virtual ~Window() = default;

    virtual void Initialize();
    virtual void Finalize();

    HWND GetHandle() const;
    SIZE GetSize() const;
    LONG GetWidth() const;
    LONG GetHeight() const;

protected:
    virtual ATOM Register() const;
    virtual HWND Create(RECT windowRect);
    virtual void Show();

    HWND _windowHandle;
    WNDCLASSEX _windowClass;
    SIZE _size;

private:
    static void PlaceInCenterOfScreen(HWND windowHandle);
    static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    int _showCommand;
};
