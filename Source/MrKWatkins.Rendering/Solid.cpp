#include "stdafx.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Textures
{
    Solid::Solid(const Material& material) : material{ material }
    {
    }

	Material Solid::GetMaterialAtPoint(const Geometry::Point& point) const
    {
        return material;
    }
}
