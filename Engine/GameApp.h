#pragma once
#include <vector>

#include "Framework.h"
#include "Logger/Logger.h"

class Scene;
class IRender;
class IDeltaUpdate;
class IInitialize;
class D2DRenderer;
class Window;

class GameApp
{
public:
   GameApp(HINSTANCE instanceHandle, int showCommand, const std::wstring& gameName);
   virtual ~GameApp();
   virtual void Initialize(bool isRelease = true, Logger::Level leastLogable = Logger::Level::Warning);
   virtual void Run();
   virtual void Finalize();

protected:
   virtual void Update();
   virtual void Render();
   virtual void AddScene(Scene* scene);

   Window* _window;
   D2DRenderer* _renderer;

   std::vector<IInitialize*> _initializeScenes;
   std::vector<IDeltaUpdate*> _deltaUpdateScene;
   std::vector<IRender*> _renderScene;

private:
   bool _isRun;
};
