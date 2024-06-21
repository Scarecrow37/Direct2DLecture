#pragma once
#include <d2d1_1.h>

struct Vector : D2D1_VECTOR_2F
{
    static Vector Zero();
    Vector(float inX, float inY);
    explicit Vector(D2D1_SIZE_F size);
    explicit Vector(SIZE size);

    operator D2D1_SIZE_F() const;
    operator D2D1_POINT_2F() const;

    Vector operator/(float rhs) const;
};
