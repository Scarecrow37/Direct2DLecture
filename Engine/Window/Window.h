#pragma once
#include "../Framework.h"

class Window
{
public:
    Window(HINSTANCE instanceHandle, int showCommand, LPCWSTR name, SIZE size);
    virtual ~Window() = default;
    virtual void Register() const;
    virtual void Create();
    virtual void Show();

protected:
    HWND _windowHandle;
    WNDCLASSEX _windowClass;
    SIZE _size;

private:
    static void PlaceInCenterOfScreen(HWND windowHandle);
    static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    int _showCommand;
};
