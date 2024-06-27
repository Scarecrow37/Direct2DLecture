#pragma once
#include "Renderer/D2DRenderer.h"
#include "Window/Window.h"

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, LPCWSTR gameName);
   GameApp(const GameApp& other) = default;
   GameApp(GameApp&& other) noexcept = default;
   GameApp& operator=(const GameApp& other) = default;
   GameApp& operator=(GameApp&& other) noexcept = default;
   virtual ~GameApp();

   virtual void Initialize();
   virtual void Finalize();
   virtual void Run();

protected:
   virtual void Update(float deltaTime);
   virtual void Render(const D2DRenderer* renderer);

   virtual void OnInitialize();
   virtual void OnUpdate(float deltaTime);
   virtual void OnRender(const D2DRenderer* renderer);

   Window* _window;
   D2DRenderer* _renderer;

private:
   std::wstring _name;
   bool _isRun;
};
