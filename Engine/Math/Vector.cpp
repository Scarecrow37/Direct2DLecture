#include "pch.h"
#include "Vector.h"

Vector Vector::Zero()
{
    return {D2D1::Vector2F()};
}

Vector Vector::Up()
{
    return {D2D1::Vector2F(0, -1)};
}

Vector Vector::Down()
{
    return {D2D1::Vector2F(0, 1)};
}

Vector Vector::Left()
{
    return {D2D1::Vector2F(-1, 0)};
}

Vector Vector::Right()
{
    return {D2D1::Vector2F(1, 0)};
}

Vector::Vector(const float inX, const float inY): D2D_VECTOR_2F({inX, inY})
{
}

Vector::Vector(const D2D1_VECTOR_2F vector) : D2D_VECTOR_2F(vector)
{
}

Vector::Vector(D2D1_POINT_2F point) : D2D_VECTOR_2F({point.x, point.y})
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

Vector Vector::operator*(const float scala) const
{
    return {x * scala, y * scala};
}

Vector Vector::operator-() const
{
    return {-x, -y};
}

Vector& Vector::operator+=(const Vector& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector Vector::operator+(const Vector& vector) const
{
    return Vector(*this) += vector;
}

Vector Vector::operator-(const Vector& other) const
{
    return *this + (-other);
}

bool Vector::operator==(const Vector& other) const
{
    return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector& other) const
{
    return !(*this == other);
}

float Vector::Size() const
{
    return sqrt(x * x + y * y);
}

Vector Vector::Normalize() const
{
    if (Size() == 0) return *this;
    return *this / Size();
}

