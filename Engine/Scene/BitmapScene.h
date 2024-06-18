#pragma once

#include "Scene.h"
#include "../Interfaces/IDeltaUpdate.h"
#include "../Interfaces/IInitialize.h"
#include "../Interfaces/IRender.h"

class D2DRenderer;
class ILoader;

class BitmapScene : public Scene, public IInitialize, public IDeltaUpdate, public IRender
{
public:
    BitmapScene(const wchar_t* path, const ILoader* loader);
    ~BitmapScene() override;
    
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render(D2DRenderer* renderer) override;

    void Load();

    void SetCenter(const Vector& center);
    Vector GetCenter() const;

protected:
    void UpdateTransform() override;

private:
    Vector _center;
    const wchar_t* _path;
    const ILoader* _loader;
    ID2D1Bitmap* _bitmap;
};
