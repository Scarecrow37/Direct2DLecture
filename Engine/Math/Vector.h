#pragma once
#include <d2d1_1.h>

struct Matrix;

struct Vector : D2D1_VECTOR_2F
{
    static Vector Zero();
    static Vector Up();
    static Vector Down();
    static Vector Left();
    static Vector Right();
    Vector(float inX, float inY);
    Vector(D2D1_VECTOR_2F vector);
    Vector(D2D1_POINT_2F point);
    Vector(D2D1_SIZE_F size);
    Vector(SIZE size);

    operator D2D1_SIZE_F() const;
    operator D2D1_POINT_2F() const;

    Vector operator/(float scala) const;
    Vector operator*(float scala) const;
    Vector operator-() const;
    Vector& operator+=(const Vector& other);
    Vector operator+(const Vector& vector) const;
};
