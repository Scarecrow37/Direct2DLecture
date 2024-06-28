#include "pch.h"
#include "Rect.h"

Rect Rect::Zero()
{
    return {D2D1::RectF()};
}

Rect::Rect(const D2D1_RECT_F rect) : D2D1_RECT_F(rect)
{
}

Rect::Rect(const Vector& point, const Vector& size)
    : D2D1_RECT_F({point.x, point.y, point.x + size.x, point.y + size.y})
{
}

Rect::Rect(const float left, const float top, const float right, const float bottom)
    : D2D1_RECT_F({left, top, right, bottom})
{
}

Vector Rect::GetSize() const
{
    return {right - left, bottom - top};
}
