#pragma once
#include "Framework.h"

class Window;

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);
   virtual ~GameApp();
   virtual void Initialize();
   virtual void Run();

protected:
   Window* _window;
};
