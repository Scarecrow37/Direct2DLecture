#pragma once
#include "Framework.h"

class D2DRenderer;
class Window;

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);
   virtual ~GameApp();
   virtual void Initialize(bool isRelease = true);
   virtual void Run();
   virtual void Finalize();

protected:
   virtual void Update();
   virtual void Render();
   
   Window* _window;
   D2DRenderer* _renderer;

private:
   bool _isRun;
};
