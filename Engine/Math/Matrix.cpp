#include "pch.h"
#include "Matrix.h"

Matrix::Matrix(D2D1_MATRIX_3X2_F matrix): D2D_MATRIX_3X2_F(matrix)
{
}

Matrix Matrix::Inverse() const
{
    Matrix inverse(*this);
    D2D1InvertMatrix(&inverse);
    return inverse;
}

Matrix Matrix::Identity()
{
    return {D2D1::Matrix3x2F::Identity()};
}

Matrix Matrix::Scale(const Vector& size, const Vector& center)
{
    return {D2D1::Matrix3x2F::Scale(size, center)};
}

Matrix Matrix::Rotation(const float angle, const Vector& center)
{
    return {D2D1::Matrix3x2F::Rotation(angle, center)};
}

Matrix Matrix::Translation(const Vector& size)
{
    return {D2D1::Matrix3x2F::Translation(size)};
}
