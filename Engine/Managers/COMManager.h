﻿#pragma once

class COMManager
{
public:
    COMManager(const COMManager& other) = delete;
    COMManager(COMManager&& other) noexcept = delete;
    COMManager& operator=(const COMManager& other) = delete;
    COMManager& operator=(COMManager&& other) noexcept = delete;
    ~COMManager();

    static void Initialize(HWND windowHandle, unsigned int width, unsigned int height);
    static void Finalize();

    static void CreateD2D1Factory(ID2D1Factory** factory);
    static void ReleaseD2D1Factory();

    static void CreateWICImagingFactory(IWICImagingFactory** imagingFactory);
    static void ReleaseWICImagingFactory();

    static void CreateDSHAnimationFactory(IDSHAnimationFactory** animationFactory);
    static void ReleaseDSHAnimationFactory();

    static void CreateD2DHwndRenderTarget(ID2D1HwndRenderTarget** hwndRenderTarget);
    static void ReleaseD2DHwndRenderTarget();

private:
    COMManager();
    static COMManager& GetInstance();

    static void InitializeCOM();
    static void InitializeFactory();
    static void InitializeImagingFactory();
    static void InitializeAnimationFactory();
    static void InitializeHwndRenderTarget(HWND windowHandle, unsigned int width, unsigned int height);

    ID2D1Factory* _factory;
    IWICImagingFactory* _imagingFactory;
    IDSHAnimationFactory* _animationFactory;
    ID2D1HwndRenderTarget* _hwndRenderTarget;
};