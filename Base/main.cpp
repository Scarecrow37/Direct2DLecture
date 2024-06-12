#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>


LRESULT DefaultWindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam);

int APIENTRY wWinMain(_In_ const HINSTANCE hInstance,
                      _In_opt_ const HINSTANCE hPrevInstance,
                      _In_ const LPWSTR lpCmdLine,
                      _In_ const int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Console
    {
        AllocConsole();
        FILE* file;
        errno_t error = freopen_s(&file, "CONOUT$", "w", stdout);
    }

    // Window
    HWND windowHandle;
    {
        // Declare window class
        WNDCLASSEX windowClass;
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = DefaultWindowProcedure;
        windowClass.cbClsExtra = NULL;
        windowClass.cbWndExtra = NULL;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = nullptr; // TODO Icon
        windowClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        windowClass.hIconSm = nullptr; // TODO Small icon;
        windowClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
        windowClass.hCursor = nullptr; // TODO Cursor;
        windowClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
        windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        windowClass.lpszMenuName = nullptr;
        windowClass.lpszClassName = nullptr; // TODO Window name;
        windowClass.lpszClassName = L"Hello, World!";

        // Register window class
        RegisterClassEx(&windowClass);

        // Create window
        // TODO AdjustWindowRect
        windowHandle = CreateWindow(windowClass.lpszClassName, /* TODO Title */ windowClass.lpszClassName,
                                    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL,
                                    nullptr, nullptr, windowClass.hInstance, nullptr);

        // Show window
        ShowWindow(windowHandle, nShowCmd);
        UpdateWindow(windowHandle);
    }

    // Direct 2D
    ID2D1Factory* factory;
    ID2D1HwndRenderTarget* renderTarget;
    ID2D1SolidColorBrush* brush;
    IDWriteFactory* writeFactory;
    IDWriteTextFormat* format;
    IWICImagingFactory* imageFactory;
            ID2D1Bitmap* bitmap;
    {
        HRESULT resultHandle = S_OK; // TODO Logging 
        resultHandle = CoInitialize(nullptr); // COM start;
        resultHandle = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
        RECT rect;
        GetClientRect(windowHandle, &rect);
        D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
        resultHandle = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                       D2D1::HwndRenderTargetProperties(windowHandle, size),
                                                       &renderTarget);

        // Brush
        {
            renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);
        }
        // Direct Write
        {
            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory));  // NOLINT(clang-diagnostic-language-extension-token)
            writeFactory->CreateTextFormat(L"Cooper", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 32.f, L"", &format);
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        }
        // Image
        {
            CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory));
            
            IWICBitmapDecoder* decoder = nullptr;
            imageFactory->CreateDecoderFromFilename(L"../Resources/Images/atk_1.png", nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
            
            IWICBitmapFrameDecode* frame = nullptr;
            decoder->GetFrame(0, &frame);
            
            IWICFormatConverter* converter = nullptr;
            imageFactory->CreateFormatConverter(&converter);
            converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
            
            renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &bitmap);
            converter->Release();
            decoder->Release();
            frame->Release();
        }
    }

    // Run
    {
        MSG message;
        while (true)
        {
            if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT) break;
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            else
            {
                // TODO Game update
                renderTarget->BeginDraw();
                renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
                D2D1_SIZE_F size = renderTarget->GetSize();
                renderTarget->DrawLine(D2D1::Point2F(0.f, 0.f),
                                       D2D1::Point2F(size.width, size.height),
                                       brush, 1.f); // brush
                WCHAR hello[] = L"Hello, World!";
                renderTarget->DrawText(hello, ARRAYSIZE(hello)-1, format, D2D1::RectF(0,0,size.width, size.height), brush); // Text
                renderTarget->DrawBitmap(bitmap);
                renderTarget->EndDraw();
            }
        }
    }

    // Direct 2D Finalize
    {
        bitmap->Release();
        imageFactory->Release();
        format->Release();
        writeFactory->Release();
        brush->Release();
        renderTarget->Release();
        factory->Release();
        CoUninitialize();
    }

    // Window Finalize
    {
        DestroyWindow(windowHandle);
    }

    // Console Finalize
    {
        FreeConsole();
    }
    return EXIT_SUCCESS;
}

LRESULT DefaultWindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
    // TODO Full screen, Window center position, Event programming, Extra commands 
    if (message == WM_DESTROY) PostQuitMessage(0);
    else return DefWindowProc(windowHandle, message, wParam, lParam);
    return 0;
}

