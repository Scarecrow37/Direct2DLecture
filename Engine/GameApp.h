#pragma once
#include "Framework.h"
#include "Logger/Logger.h"

class D2DRenderer;
class Window;

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);
   virtual ~GameApp();
   virtual void Initialize(bool isRelease = true, Logger::Level leastLogable = Logger::Level::Warning);
   virtual void Run();
   virtual void Finalize();

protected:
   virtual void Update();
   virtual void Render();

   virtual void OnUpdate(float deltaTime); // TODO Remove when created content update.
   virtual void OnRender(const D2DRenderer* renderer); // TODO Remove when created content render.

   Window* _window;
   D2DRenderer* _renderer;

private:
   bool _isRun;
};
