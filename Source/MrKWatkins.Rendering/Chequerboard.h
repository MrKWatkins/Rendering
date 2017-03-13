#pragma once
#include "Texture.h"

namespace MrKWatkins::Rendering::Textures
{
    class Chequerboard final : public Texture
    {
		Material material1;
		Material material2;
        double size;
    public:
        Chequerboard(const Material& material1, const Material& material2, double size);

		Material GetMaterialAtPoint(const Geometry::Point& point) const override;
    };
}
