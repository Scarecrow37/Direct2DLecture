#pragma once
#include "ILoader.h"

class D2DRenderer;

class BitmapLoader : public ILoader
{
public:
    BitmapLoader(const D2DRenderer* renderer);
    void Load(const wchar_t* path, void* container) const override;

private:
    const D2DRenderer* _renderer;
};
