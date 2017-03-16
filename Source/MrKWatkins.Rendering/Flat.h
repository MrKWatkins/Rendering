#pragma once
#include "Texture.h"

namespace MrKWatkins::Rendering::Textures
{
    class Flat final : public Texture
    {
		Material material;
    public:
        explicit Flat(const Material& material);

		Material GetMaterialAtPoint(const Geometry::Point& point) const override;
    };
}
