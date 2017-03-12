#pragma once
#include "Texture.h"

namespace MrKWatkins::Rendering::Textures
{
    class SkyGradient final : public Texture
    {
        Colour horizonColour;
        Colour zenithColour;
    public:
        explicit SkyGradient(const Colour& horizonColour, const Colour& zenithColour);

        Colour GetColourAtPoint(const Geometry::Point& point) const override;
    };
}
