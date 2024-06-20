#pragma once
#include "RenderTarget.h"

class Factory
{
public:
    explicit Factory(const std::shared_ptr<ILoggerUnicode>& logger);
    Factory(const Factory& other) = default;
    Factory(Factory&& other) noexcept = default;
    Factory& operator=(const Factory& other) = default;
    Factory& operator=(Factory&& other) noexcept = default;
    ~Factory();

    void Initialize();
    void CreateHwndRenderTarget(RenderTarget& renderTarget, HWND windowHandle, unsigned int width, unsigned int height) const;

private:
    std::shared_ptr<ILoggerUnicode> _logger;

    ID2D1Factory* _factory;
};
