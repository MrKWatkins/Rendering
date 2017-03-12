#include "stdafx.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Textures
{
    Solid::Solid(const Colour& colour) : colour { colour }
    {
    }

    Colour Solid::GetColourAtPoint(const Geometry::Point& point) const
    {
        return colour;
    }
}
