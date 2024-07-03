#pragma once

struct Rect : D2D1_RECT_F
{
    static Rect Zero();
    Rect(D2D1_RECT_F rect);
    Rect(const Vector& point, const Vector& size);
    Rect(float left, float top, float right, float bottom);

    Vector GetSize() const;
    Vector GetCenter() const;
    Vector GetExtend() const;
};
