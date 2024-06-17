#include "GameApp.h"

#include "Logger/Logger.h"
#include "Window/Window.h"
#include "Renderer/D2DRenderer.h"
#include "TimeSystem/Time.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const wchar_t* gameName):
    _window(new Window(instanceHandle, showCommand, gameName, {1920, 1080})), _renderer(new D2DRenderer),
    _isRun(false)
{
}

GameApp::~GameApp()
{
    delete _window;
}

void GameApp::Initialize(const bool isRelease, const Logger::Level leastLogable)
{
    Logger::Initialize(!isRelease);
    Logger::SetLeastLogable(leastLogable);
    Logger::Log(Logger::Level::Debug, "Initialize start.");
    try
    {
        _window->Initialize();
        Logger::Log(Logger::Level::Trace, "Window is initialized.");
        _renderer->Initialize(_window->GetHandle(), _window->GetWidth(), _window->GetHeight());
        Logger::Log(Logger::Level::Trace, "Renderer is initialized.");
        _isRun = true;
        Logger::Log(Logger::Level::Debug, "Initialize end.");
    }
    catch (const std::exception& exception)
    {
        Logger::Log(Logger::Level::Error, exception.what());
        Logger::Log(Logger::Level::Fatal, "Initialize fail.");
        _isRun = false;
    }
}

void GameApp::Run()
{
    MSG message;
    while (_isRun)
    {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
            {
                Logger::Log(Logger::Level::Info, "Receive WM_QUIT message.");
                break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            Update();
            Render();
        }
    }
}

void GameApp::Finalize()
{
    Logger::Log(Logger::Level::Debug, "Finalize start.");
    _renderer->Finalize();
    Logger::Log(Logger::Level::Trace, "Renderer is finalized.");
    _window->Finalize();
    Logger::Log(Logger::Level::Trace, "Window is finalized.");
    Logger::Log(Logger::Level::Debug, "Finalize end.");
}

void GameApp::Update()
{
    Logger::Log(Logger::Level::Debug, "Update start.");
    Time::Update();
    Logger::Log(Logger::Level::Trace, "Time is updated.");
    // TODO Input
    // TODO Content
    OnUpdate(Time::GetDeltaTime());
    // TODO UI
    Logger::Log(Logger::Level::Debug, "Update end.");
}

void GameApp::Render()
{
    Logger::Log(Logger::Level::Debug, "Render start.");
    try
    {
        _renderer->BeginDraw();
        // TODO Content
        OnRender(_renderer);
        _renderer->EndDraw();
        Logger::Log(Logger::Level::Debug, "Render end.");
    }
    catch (const std::exception& exception)
    {
        Logger::Log(Logger::Level::Error, exception.what());
        Logger::Log(Logger::Level::Fatal, "Rendering is fail.");
        _isRun = false;
    }
}

void GameApp::OnUpdate(float deltaTime)
{
}

void GameApp::OnRender(const D2DRenderer* renderer)
{
}
