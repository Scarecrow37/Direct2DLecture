#pragma once

struct Rect : D2D1_RECT_F
{
    static Rect Zero();
    Rect(D2D1_RECT_F rect);
    Rect(const Vector& point, const Vector& size);

    Vector GetSize() const;
};
