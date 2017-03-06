#pragma once
#include "Material.h"

namespace MrKWatkins::Rendering::Materials
{
    class Chequerboard : public Material
    {
        Colour colour1;
        Colour colour2;
        double size;
    public:
        explicit Chequerboard(const Colour& colour1, const Colour& colour2, double size);

        Colour GetColourAtPoint(const Geometry::Point& point) const override;
    };
}
