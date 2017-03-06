#pragma once
#include "Material.h"

namespace MrKWatkins::Rendering::Materials
{
    class SkyGradient : public Material
    {
        Colour horizonColour;
        Colour zenithColour;
    public:
        explicit SkyGradient(const Colour& horizonColour, const Colour& zenithColour);

        Colour GetColourAtPoint(const Geometry::Point& point) const override;
    };
}
