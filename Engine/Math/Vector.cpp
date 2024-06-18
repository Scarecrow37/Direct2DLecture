#include "Vector.h"

Vector Vector::Zero()
{
    return {0.f, 0.f};
}

Vector::Vector(const float inX, const float inY): D2D_VECTOR_2F({inX, inY})
{
}

Vector::Vector(const D2D1_SIZE_F size) : D2D_VECTOR_2F({size.width, size.height})
{
}

Vector::operator D2D_SIZE_F() const
{
    return D2D1::Size(x, y);
}

Vector::operator D2D_POINT_2F() const
{
    return D2D1::Point2F(x, y);
}

Vector Vector::operator/(const float rhs) const
{
    return {x / rhs, y / rhs};
}

