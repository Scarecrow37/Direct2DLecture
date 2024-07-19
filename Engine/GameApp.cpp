#include "pch.h"
#include "GameApp.h"

#include "Managers/COMManager.h"
#include "Managers/ResourceManager.h"
#include "Window/Window.h"
#include "Renderer/D2DRenderer.h"
#include "World/World.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName):
    _window(new Window(instanceHandle, showCommand, gameName, {1920, 1080})),
    _renderer(new D2DRenderer),
    _world(new World(Rect{0, 0, 1920, 1080})), _isRun(false)
{
    Logger::Log(LogLevel::Trace, L"GameApp constructor start.");
    Logger::Log(LogLevel::Trace, L"GameApp constructor end.");
}

GameApp::~GameApp()
{
    delete _world;
    _world = nullptr;
    delete _renderer;
    _renderer = nullptr;
    delete _window;
    _window = nullptr;
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
        CameraManager::Initialize(_world, _renderer);
        ResourceManager::Initialize();
        Time::Initialize();
        Input::Initialize(_window->GetHandle());
        _world->Initialize();
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
    CameraManager::Finalize();
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
                Update(Time::GetDeltaTime());
                LazyUpdate(Time::GetDeltaTime());
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
        Time::Update();
        Input::Update();
        _world->Update(deltaTime);
        OnUpdate(deltaTime);
        CameraManager::Update();
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

void GameApp::LazyUpdate(float deltaTime)
{
    _world->LazyUpdate(deltaTime);
    Input::Reset();
}

void GameApp::Render(const D2DRenderer* renderer)
{
    try
    {
        Logger::Log(LogLevel::Trace, L"GameApp render start.");
        renderer->BeginDraw();
        _world->Render(renderer);
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
