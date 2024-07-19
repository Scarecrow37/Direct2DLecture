#pragma once
#include "Scene.h"
#include "../Component/Component.h"

class BoxScene : public Scene, public Component
{
public:
    BoxScene();
    explicit BoxScene(const Scene* parent);

    void Initialize() override;
    void Update(float deltaTime) override;
    void LazyUpdate(float deltaTime) override;

    Rect GetRect() const;
    void SetRect(const Rect& rect);

    D2D1::ColorF GetColor() const;
    void SetColor(const D2D1::ColorF& color);

protected:
    void UpdateCenterTransform() override;
    
    Rect _rect;
    D2D1::ColorF _color;
};
