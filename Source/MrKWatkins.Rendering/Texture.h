#pragma once
#include "Colour.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Textures
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual Colour GetColourAtPoint(const Geometry::Point& point) const = 0;
    };
}
