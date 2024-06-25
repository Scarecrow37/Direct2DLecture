#include "pch.h"
#include "SolarSystemApp.h"


SolarSystemApp::SolarSystemApp(const HINSTANCE instanceHandle, const int showCommand, const LPCWSTR gameName)
    : GameApp(instanceHandle, showCommand, gameName), _sun(), _earth(&_sun), _moon(&_earth)
{
    Logger::SetLeastLoglevel(LogLevel::Warning);
    Logger::Log(LogLevel::Trace, L"SolarSystemApp constructor start.");
    Logger::Log(LogLevel::Trace, L"SolarSystemApp constructor end.");
}

void SolarSystemApp::OnInitialize()
{
    _sun.Load(_renderer, L"../Resources/Images/Solar.png");
    _sun.SetCenter({0.5f, 0.5f});
    _sun.SetScale({0.2f, 0.2f});
    _sun.SetTranslation(Vector(_window->GetSize()) / 2);

    _earth.Load(_renderer, L"../Resources/Images/Earth.png");
    _earth.SetCenter({0.5f, 0.5f});
    _earth.SetScale({0.4f, 0.4f});
    _earth.SetTranslation(Vector(_window->GetSize()));

    _moon.Load(_renderer, L"../Resources/Images/Moon.png");
    _moon.SetCenter({0.5f, 0.5f});
    _moon.SetScale({0.1f, 0.1f});
    _moon.SetTranslation(Vector(_window->GetSize()));
}

void SolarSystemApp::OnUpdate(const float deltaTime)
{
    _sun.SetRotation(_sun.GetRotation() + deltaTime * 40.f);
    _sun.Update(deltaTime);

    _earth.SetRotation(_earth.GetRotation() + deltaTime * 20.f);
    _earth.Update(deltaTime);

    _moon.SetRotation(_moon.GetRotation() + deltaTime * 10.f);
    _moon.Update(deltaTime);
}

void SolarSystemApp::OnRender(const D2DRenderer* renderer)
{
    _sun.Render(renderer);
    _earth.Render(renderer);
    _moon.Render(renderer);
}
