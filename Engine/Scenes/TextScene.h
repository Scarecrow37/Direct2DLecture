#pragma once
#include "Scene.h"
#include "../Component/Component.h"

class TextScene : public Scene, public Component
{
public:
    TextScene();
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

    void SetText(const std::wstring& text);
    std::wstring GetText() const;

    void SetTextBound(const Rect& textBound);
    Rect GetTextBound() const;

    void SetFontSize(float fontSize);
    float GetFontSize() const;

protected:
    void UpdateCenterTransform() override;
    std::wstring _text;
    Rect _textBound;
    float _fontSize;
};
