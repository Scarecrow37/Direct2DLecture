#include "pch.h"
#include "BoxColliderScene.h"

#include "../Renderer/D2DRenderer.h"

BoxColliderScene::BoxColliderScene() : ColliderScene(ColliderType::Box)
{
}

bool BoxColliderScene::IsCollide(ColliderScene* otherColliderScene,Manifold* manifold)
{
    if (otherColliderScene->GetColliderType() == ColliderType::Box)
    {
        const BoxColliderScene* otherBoxCollider = dynamic_cast<BoxColliderScene*>(otherColliderScene);
        assert(otherBoxCollider != nullptr);
        return _bound.CheckIntersect(otherBoxCollider->_bound, manifold);
    }
    // TODO: Implement other collider type
    return false;
}

void BoxColliderScene::SetBound(const AABB bound)
{
    _bound = bound;
}

void BoxColliderScene::SetBound(const Vector& size)
{
    _bound = AABB(Rect{Vector{0, 0}, size});
}

void BoxColliderScene::UpdateCenterTransform()
{
    const Vector boundSize = _bound.GetRect().GetSize();
    _centerMatrix = D2D1::Matrix3x2F::Translation({boundSize.x * -_center.x, boundSize.y * -_center.y});
}

void BoxColliderScene::UpdateColliderBound()
{
    
    _bound.SetCenter(_bound.GetExtend() * (_centerMatrix * _worldTransform));
}

void BoxColliderScene::Initialize()
{
}

void BoxColliderScene::Update(float deltaTime)
{
    UpdateTransform();
    UpdateColliderBound();
}

void BoxColliderScene::LazyUpdate(float deltaTime)
{
}

void BoxColliderScene::Render(const D2DRenderer* renderer) const
{
    renderer->SetTransform(_centerMatrix * _worldTransform * renderer->GetCameraMatrix());
    renderer->DrawRectangle({{0,0}, _bound.GetRect().GetSize()});
}
