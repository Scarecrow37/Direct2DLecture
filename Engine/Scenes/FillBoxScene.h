#pragma once
#include "BoxScene.h"

class FillBoxScene : public BoxScene
{
public:
    void Render(const D2DRenderer* renderer) const override;
};
