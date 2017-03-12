#pragma once
#include "Texture.h"

namespace MrKWatkins::Rendering::Textures
{
    class Solid final : public Texture
    {
        Colour colour;
    public:
        explicit Solid(const Colour& colour);

        Colour GetColourAtPoint(const Geometry::Point& point) const override;
    };
}
