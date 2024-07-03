#include "pch.h"
#include "BoxScene.h"

BoxScene::BoxScene() : BoxScene(nullptr)
{
}

BoxScene::BoxScene(const Scene* parent) : Scene(parent), _rect(Rect::Zero()), _color(D2D1::ColorF::White)
{
}

void BoxScene::Update(const float deltaTime)
{
    Logger::Log(LogLevel::Trace, L"BoxScene update start.");
    UpdateTransform();
    Logger::Log(LogLevel::Trace, L"BoxScene update end.");
}

Rect BoxScene::GetRect() const
{
    return _rect;
}

void BoxScene::SetRect(const Rect& rect)
{
    _rect = rect;
}

D2D1::ColorF BoxScene::GetColor() const
{
    return _color;
}

void BoxScene::SetColor(const D2D1::ColorF& color)
{
    _color = color;
}

void BoxScene::UpdateCenterTransform()
{
    Logger::Log(LogLevel::Trace, L"BoxScene update center transform start.");
    _centerMatrix = Matrix::Translation({_rect.GetSize().x * -_center.x, _rect.GetSize().y * -_center.y});
    Logger::Log(LogLevel::Trace, L"BoxScene update center transform end.");
}
