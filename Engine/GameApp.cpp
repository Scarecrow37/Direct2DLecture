#include "GameApp.h"

#include "Logger/Logger.h"
#include "Window/Window.h"
#include "Renderer/D2DRenderer.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* gameName):
    _window(new Window(instanceHandle, showCommand, gameName, {1920, 1080})), _renderer(new D2DRenderer),
    _isInitialized(false)
{
}

GameApp::~GameApp()
{
    delete _window;
}

void GameApp::Initialize(const bool isRelease)
{
    Logger::Initialize(!isRelease);
    try
    {
        _window->Initialize();
        _renderer->Initialize(_window->GetHandle(), _window->GetWidth(), _window->GetHeight());
        _isInitialized = true;
    }
    catch (std::exception& exception)
    {
        Logger::Log(Logger::Level::Error, exception.what());
        _isInitialized = false;
    }
}

void GameApp::Run()
{
}
