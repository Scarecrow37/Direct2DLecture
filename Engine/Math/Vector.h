#pragma once
#include <d2d1_1.h>

struct Vector : D2D1_VECTOR_2F
{
    static constexpr Vector Zero = {0.f, 0.f};
    Vector(float inX, float inY);

    operator D2D1_SIZE_F() const
    {
        return D2D1::Size(x, y);
    }

    operator D2D1_POINT_2F() const
    {
        return D2D1::Point2F(x, y);
    }
};
