﻿#pragma once

class Window;
class D2DRenderer;

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName,
           const std::shared_ptr<ILoggerUnicode>& logger);
   GameApp(const GameApp& other) = default;
   GameApp(GameApp&& other) noexcept = default;
   GameApp& operator=(const GameApp& other) = default;
   GameApp& operator=(GameApp&& other) noexcept = default;
   virtual ~GameApp();

   virtual void Initialize();
   virtual void Run();
   virtual void Finalize();

protected:
   virtual void Update();
   virtual void Render();

   std::shared_ptr<ILoggerUnicode> _logger;

   Window* _window;
   D2DRenderer* _renderer;

private:
   std::wstring _name;
   bool _isRun;
};
