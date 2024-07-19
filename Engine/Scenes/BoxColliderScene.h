#pragma once
#include "ColliderScene.h"

class BoxColliderScene
    : public ColliderScene
{
public:
    BoxColliderScene();

    bool IsCollide(ColliderScene* otherColliderScene, Manifold* manifold) override;
    void SetBound(AABB bound);
    void SetBound(const Vector& size);

protected:
    void UpdateCenterTransform() override;
    virtual void UpdateColliderBound();

public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void LazyUpdate(float deltaTime) override;
    void Render(const D2DRenderer* renderer) const override;

private:
    AABB _bound;
};
