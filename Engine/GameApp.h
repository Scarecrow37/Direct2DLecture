#pragma once
#include "Window/Window.h"

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, const wchar_t* gameName);
   virtual ~GameApp() = default;
   virtual void Initialize();
   virtual void Run();

   Window _window;
};
