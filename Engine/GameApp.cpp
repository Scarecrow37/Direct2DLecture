#include "GameApp.h"

#include "Logger/Logger.h"
#include "Window/Window.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* gameName):
    _window(new Window(instanceHandle, showCommand, gameName, {1920, 1080}))
{
}

GameApp::~GameApp()
{
    delete _window;
}

void GameApp::Initialize()
{
    Logger::Initialize();
    _window->Register();
    _window->Create();
    _window->Show();
}

void GameApp::Run()
{
}
