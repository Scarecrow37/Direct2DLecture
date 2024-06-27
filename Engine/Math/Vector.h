#pragma once
#include <d2d1_1.h>

struct Vector : D2D1_VECTOR_2F
{
    static Vector Zero();
    Vector(float inX, float inY);
    Vector(D2D1_VECTOR_2F vector);
    Vector(D2D1_SIZE_F size);
    Vector(SIZE size);

    operator D2D1_SIZE_F() const;
    operator D2D1_POINT_2F() const;

    Vector operator/(float scala) const;
};
