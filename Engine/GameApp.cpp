#include "pch.h"
#include "GameApp.h"

#include "Managers/COMManager.h"
#include "Managers/ResourceManager.h"
#include "Window/Window.h"
#include "Renderer/D2DRenderer.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName):
    _window(new Window(instanceHandle, showCommand, gameName, {1920, 1080})),
    _renderer(new D2DRenderer),
    _isRun(false)
{
    Logger::Log(LogLevel::Trace, L"GameApp constructor start.");
    Logger::Log(LogLevel::Trace, L"GameApp constructor end.");
}

GameApp::~GameApp()
{
    delete _renderer;
    delete _window;
}

void GameApp::Initialize()
{
    try
    {
        Logger::Log(LogLevel::Trace, L"GameApp initialize start.");
        Logger::Initialize();
        _window->Initialize();
        COMManager::Initialize(_window->GetHandle(), _window->GetWidth(), _window->GetHeight());
        _renderer->Initialize();
        ResourceManager::Initialize();
        Time::Initialize();
        OnInitialize();
        _isRun = true;
        Logger::Log(LogLevel::Trace, L"GameApp initialize end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        Logger::Log(LogLevel::Fatal, L"GameApp initialize fail.");
        _isRun = false;
    }
}

void GameApp::Finalize()
{
    Time::Finalize();
    ResourceManager::Finalize();
    _renderer->Finalize();
    COMManager::Finalize();
    _window->Finalize();
    Logger::Finalize();
}

void GameApp::Run()
{
    try
    {
        Logger::Log(LogLevel::Trace, L"GameApp run start.");
        MSG message;
        while (_isRun)
        {
            if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT)
                {
                    Logger::Log(LogLevel::Information, L"Receive WM_QUIT message.");
                    break;
                }
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            else
            {
                Time::Update();
                // TODO Input
                Update(Time::GetDeltaTime());
                Render(_renderer);
            }
        }
        Logger::Log(LogLevel::Trace, L"GameApp run end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        Logger::Log(LogLevel::Fatal, L"GameApp run fail.");
        _isRun = false;
    }
}

void GameApp::Update(const float deltaTime)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"GameApp update start.");
        OnUpdate(deltaTime);
        // TODO UI
        Logger::Log(LogLevel::Trace, L"GameApp update end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        Logger::Log(LogLevel::Fatal, L"GameApp update fail.");
        throw;
    }
}

void GameApp::Render(const D2DRenderer* renderer)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"GameApp render start.");
        renderer->BeginDraw();
        OnRender(renderer);
        // TODO UI
        renderer->EndDraw();
        Logger::Log(LogLevel::Trace, L"GameApp render end.");
    }
    catch (const Exception& exception)
    {
        Logger::Log(LogLevel::Error, exception.UnicodeWhat());
        Logger::Log(LogLevel::Fatal, L"GameApp render fail.");
        throw;
    }
}

void GameApp::OnInitialize()
{
}

void GameApp::OnUpdate(float deltaTime)
{
}

void GameApp::OnRender(const D2DRenderer* renderer)
{
}
