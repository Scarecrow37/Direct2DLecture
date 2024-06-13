#pragma once
#include "../Framework.h"
#include "../Interfaces/IFinalize.h"
#include "../Interfaces/IInitialize.h"

class Window : public IInitialize, public IFinalize
{
public:
    Window(HINSTANCE instanceHandle, int showCommand, LPCWSTR name, SIZE size);
    ~Window() override = default;

    void Initialize() override;
    void Finalize() override;

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
