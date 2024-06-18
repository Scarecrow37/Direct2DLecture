#pragma once
#include "../Engine/GameApp.h"

class BitmapLoader;class DemoApp final : public GameApp
{
public:
    DemoApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);

    void Initialize(bool isRelease = true, Logger::Level leastLogable = Logger::Level::Warning) override;
private:
    BitmapLoader* _bitmapLoader;
};
