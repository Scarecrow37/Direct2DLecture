#pragma once
#include <d2d1.h>

#include "Vector.h"

struct Matrix : D2D1_MATRIX_3X2_F
{
    static Matrix Scale(const Vector& size, const Vector& center = Vector::Zero());
    static Matrix Rotation(float angle, const Vector& center = Vector::Zero());
    static Matrix Translation(const Vector& size);

    Matrix(D2D1_MATRIX_3X2_F matrix);

    Matrix Inverse() const;
};
