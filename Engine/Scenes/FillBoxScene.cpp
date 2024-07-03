#include "pch.h"
#include "FillBoxScene.h"
#include "../Renderer/D2DRenderer.h"

void FillBoxScene::Render(const D2DRenderer* renderer) const
{
    Logger::Log(LogLevel::Trace, L"EmptyBoxScene render start.");
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->FillRectangle(_rect, _color);
    Logger::Log(LogLevel::Trace, L"EmptyBoxScene render end.");
}
