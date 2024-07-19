#include "pch.h"
#include "Platform.h"

#include "../../../Engine/Scenes/EmptyBoxScene.h"
#include "../../../Engine/Scenes/BoxColliderScene.h"
#include "../../../Engine/Scenes/FillBoxScene.h"

Platform::Platform()
{
    _positionRenderBox = CreateComponent<EmptyBoxScene>();
    SetRootScene(_positionRenderBox);
    _positionRenderBox->SetColor(D2D1::ColorF::Purple);
    _positionRenderBox->SetRect({0,0,2,2});
    _positionRenderBox->SetCenter(Vector::HalfOne());

    _platformRenderBox = CreateComponent<FillBoxScene>();
    _platformRenderBox->SetParentScene(_rootScene);
    _platformRenderBox->SetColor(D2D1::ColorF::Purple);
    _platformRenderBox->SetRect({0,0,1024,128});
    _platformRenderBox->SetCenter(Vector::HalfOne());

    _colliderScene = CreateComponent<BoxColliderScene>();
    _colliderScene->SetParentScene(_rootScene);
    _colliderScene->SetNotify(this);
    _colliderScene->SetCollisionType(CollisionType::Block);
    _colliderScene->SetBound(_platformRenderBox->GetRect());
    _colliderScene->SetCenter(Vector::HalfOne());

    _rootScene->SetTranslation({0, 500});
}

void Platform::OnBlock(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Platform::OnBeginOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Platform::OnEndOverlap(ColliderScene* ownedCollider, ColliderScene* otherCollider, Manifold manifold)
{
}

void Platform::UpdateBoundBox()
{
    _boundBox.SetExtend(_platformRenderBox->GetRect().GetExtend());
    _boundBox.SetCenter({GetWorldLocation().x, GetWorldLocation().y});
}


