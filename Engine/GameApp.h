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

protected:
   Window* _window;
   D2DRenderer* _renderer;

private:
   bool _isInitialized;
};
