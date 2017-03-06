#pragma once
#include "Material.h"

namespace MrKWatkins::Rendering::Materials
{
    class Solid : public Material
    {
        Colour colour;
    public:
        explicit Solid(const Colour& colour);

        Colour GetColourAtPoint(const Geometry::Point& point) const override;
    };
}
