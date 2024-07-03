#include "pch.h"
#include "EmptyBoxScene.h"
#include "../Renderer/D2DRenderer.h"

void EmptyBoxScene::Render(const D2DRenderer* renderer) const
{
    Logger::Log(LogLevel::Trace, L"EmptyBoxScene render start.");
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawRectangle(_rect, _color);
    Logger::Log(LogLevel::Trace, L"EmptyBoxScene render end.");
}
