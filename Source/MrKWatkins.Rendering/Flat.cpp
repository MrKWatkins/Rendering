#include "stdafx.h"
#include "Flat.h"

namespace MrKWatkins::Rendering::Textures
{
	Flat::Flat(const Material& material) : material{ material }
    {
    }

	Material Flat::GetMaterialAtPoint(const Geometry::Point& point) const
    {
        return material;
    }
}
