#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Uniform::ShadePoint(Scene::Scene& scene, Geometry::Point point, Colour colourOfPoint, Geometry::Vector surfaceNormal) const
    {
        return colourOfPoint;
    }
}
