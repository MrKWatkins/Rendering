#include "stdafx.h"
#include "Point.h"
#include "Colour.h"
#include "Chequerboard.h"

namespace MrKWatkins::Rendering::Materials
{
    Chequerboard::Chequerboard(const Colour& colour1, const Colour& colour2, double size) : colour1{ colour1 }, colour2{ colour2 }, size{ size }
    {
    }

    Colour Chequerboard::GetColourAtPoint(const Geometry::Point& point) const
    {
        auto x = int(round(point.X() / size));
        auto y = int(round(point.Y() / size));
        auto z = int(round(point.Z() / size));

        if ((x + y + z & 1) == 0)
        {
            return colour1;
        }
        return colour2;
    }
}