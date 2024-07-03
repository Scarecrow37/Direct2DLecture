#pragma once
#include "BoxScene.h"

class EmptyBoxScene : public BoxScene
{
public:
    void Render(const D2DRenderer* renderer) const override;
};
