#include "pch.h"
#include "TextScene.h"

#include "../Renderer/D2DRenderer.h"

TextScene::TextScene(): _textBound(Rect::Zero())
{
}

void TextScene::Initialize()
{
}

void TextScene::Update(float deltaTime)
{
    UpdateTransform();
}

void TextScene::Render(const D2DRenderer* renderer) const
{
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawTextW(_text, _fontSize, _textBound);
}

void TextScene::SetText(const std::wstring& text)
{
    _text = text;
}

std::wstring TextScene::GetText() const
{
    return _text;
}

void TextScene::SetTextBound(const Rect& textBound)
{
    _textBound = textBound;
}

Rect TextScene::GetTextBound() const
{
    return _textBound;
}

void TextScene::UpdateCenterTransform()
{
    _centerMatrix = Matrix::Translation(-_textBound.GetExtend());
}

void TextScene::SetFontSize(const float fontSize)
{
    _fontSize = fontSize;
}

float TextScene::GetFontSize() const
{
    return _fontSize;
}

