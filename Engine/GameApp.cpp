﻿#include "pch.h"
#include "GameApp.h"

#include "Window/Window.h"
#include "Renderer/D2DRenderer.h"

GameApp::GameApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName,
                 const std::shared_ptr<ILoggerUnicode>& logger):
    _logger(logger),
    _window(instanceHandle, showCommand, gameName, {1920, 1080}, _logger),
    _renderer(_logger),
    _isRun(false)
{
    _logger->Log(LogLevel::Trace, L"GameApp constructor start.");
    _logger->Log(LogLevel::Trace, L"GameApp constructor end.");
}

void GameApp::Initialize()
{
    try
    {
        _logger->Log(LogLevel::Trace, L"GameApp initialize start.");
        _window.Initialize();
        _renderer.Initialize(_window.GetHandle(), _window.GetWidth(), _window.GetHeight());
        Time::Initialize();
        // for (const auto& scene : _initializeScenes)
        // {
        //     scene->Initialize();
        // }
        _isRun = true;
        _logger->Log(LogLevel::Trace, L"GameApp initialize end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        _logger->Log(LogLevel::Fatal, L"GameApp initialize fail.");
        _isRun = false;
    }
}

void GameApp::Run()
{
    try
    {
        _logger->Log(LogLevel::Trace, L"GameApp run start.");
        MSG message;
        while (_isRun)
        {
            if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
            {
                if (message.message == WM_QUIT)
                {
                    _logger->Log(LogLevel::Information, L"Receive WM_QUIT message.");
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
        _logger->Log(LogLevel::Trace, L"GameApp run end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        _logger->Log(LogLevel::Fatal, L"GameApp run fail.");
        _isRun = false;
    }
}

void GameApp::Update()
{
    try
    {
        _logger->Log(LogLevel::Trace, L"GameApp update start.");
        Time::Update();
        // TODO Input
        // for (const auto& scene : _deltaUpdateScene)
        // {
        //     scene->Update(Time::GetDeltaTime());
        // }
        // TODO UI
        _logger->Log(LogLevel::Trace, L"GameApp update end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        _logger->Log(LogLevel::Fatal, L"GameApp update fail.");
        throw;
    }
}

void GameApp::Render()
{
    try
    {
        _logger->Log(LogLevel::Trace, L"GameApp render start.");
        _renderer.BeginDraw();
        // TODO Content
        // for (const auto& scene : _renderScene)
        // {
        //     scene->Render(_renderer);
        // }
        _renderer.EndDraw();
        _logger->Log(LogLevel::Trace, L"GameApp render end.");
    }
    catch (const Exception& exception)
    {
        _logger->Log(LogLevel::Error, exception.UnicodeWhat());
        _logger->Log(LogLevel::Fatal, L"GameApp render fail.");
        throw;
    }
}
