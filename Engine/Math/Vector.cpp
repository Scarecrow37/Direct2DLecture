#include "pch.h"
#include "Vector.h"

Vector Vector::Zero()
{
    return {D2D1::Vector2F()};
}

Vector::Vector(const float inX, const float inY): D2D_VECTOR_2F({inX, inY})
{
}

Vector::Vector(const D2D1_VECTOR_2F vector) : D2D_VECTOR_2F(vector)
{
}

Vector::Vector(const D2D1_SIZE_F size) : D2D_VECTOR_2F({size.width, size.height})
{
}

Vector::Vector(const SIZE size) : D2D_VECTOR_2F({static_cast<float>(size.cx), static_cast<float>(size.cy)})
{
}

Vector::operator D2D_SIZE_F() const
{
    return {D2D1::Size(x, y)};
}

Vector::operator D2D_POINT_2F() const
{
    return {D2D1::Point2F(x, y)};
}

Vector Vector::operator/(const float scala) const
{
    return {x / scala, y / scala};
}

