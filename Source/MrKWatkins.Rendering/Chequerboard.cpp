#include "stdafx.h"
#include "Point.h"
#include "Material.h"
#include "Chequerboard.h"

namespace MrKWatkins::Rendering::Textures
{
    Chequerboard::Chequerboard(const Material& material1, const Material& material2, double size) : material1{ material1 }, material2{ material2 }, size{ size }
    {
    }

    Material Chequerboard::GetMaterialAtPoint(const Geometry::Point& point) const
    {
        auto x = int(round(point.X() / size));
        auto y = int(round(point.Y() / size));
        auto z = int(round(point.Z() / size));

        if ((x + y + z & 1) == 0)
        {
            return material1;
        }
        return material2;
    }
}