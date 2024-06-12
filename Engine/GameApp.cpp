#include "GameApp.h"

#include "Logger/Logger.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* gameName):
    _window(instanceHandle, showCommand, gameName, {1920, 1080})
{
}

void GameApp::Initialize()
{
    Logger::Initialize();
    _window.Register();
    _window.Create();
    _window.Show();
}

void GameApp::Run()
{
}
