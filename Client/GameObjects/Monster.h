#pragma once
#include "../../Engine/GameObject/GameObject.h"

class Monster : public GameObject
{
public:
    Monster();

    void SetTranslation(const Vector& translation) const;
};
