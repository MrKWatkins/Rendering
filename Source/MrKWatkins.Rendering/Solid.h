#pragma once
#include "Texture.h"

namespace MrKWatkins::Rendering::Textures
{
    class Solid final : public Texture
    {
		Material material;
    public:
        explicit Solid(const Material& material);

		Material GetMaterialAtPoint(const Geometry::Point& point) const override;
    };
}
