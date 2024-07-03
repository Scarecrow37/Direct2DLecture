#include "pch.h"
#include "Monster.h"

#include "../../Engine/Scenes/FillBoxScene.h"

Monster::Monster()
{
    FillBoxScene* boxScene = CreateComponent<FillBoxScene>();
    SetRootScene(boxScene);
    boxScene->SetColor(D2D1::ColorF::Red);
    boxScene->SetCenter({0.5f, 0.5f});
    boxScene->SetRect(Rect(0, 0, 50, 50));
    
    SetBoundBox(boxScene->GetRect());
}

void Monster::SetTranslation(const Vector& translation) const
{
    _rootScene->SetTranslation(translation);
}
