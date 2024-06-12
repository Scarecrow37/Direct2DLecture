#pragma once
#include "../Framework.h"

class Window
{
public:
    Window(HINSTANCE instanceHandle,int showCommand, LPCWSTR name, SIZE size);
    void Register() const;
    void Create();
    void Show();

private:
    static void PlaceInCenterOfScreen(HWND windowHandle);
    static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
    
    HWND _windowHandle;
    int _showCommand;
    WNDCLASSEX _windowClass;
    SIZE _size;
};
