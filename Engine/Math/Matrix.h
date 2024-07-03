#pragma once
#include <d2d1.h>

#include "Vector.h"

struct Matrix : D2D1::Matrix3x2F
{
    static Matrix Identity();
    static Matrix Scale(const Vector& size, const Vector& center = Vector::Zero());
    static Matrix Rotation(float angle, const Vector& center = Vector::Zero());
    static Matrix Translation(const Vector& size);

    Matrix(Matrix3x2F matrix);
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) noexcept = default;
    ~Matrix() = default;

    Matrix Inverse() const;
};
