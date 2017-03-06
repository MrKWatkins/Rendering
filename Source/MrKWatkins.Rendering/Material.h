#pragma once
#include "Colour.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Materials
{
    class Material
    {
    public:
        virtual ~Material() = default;

        virtual Colour GetColourAtPoint(const Geometry::Point& point) const = 0;
    };
}
