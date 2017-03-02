#include "stdafx.h"
#include "PointLight.h"
#include "AmbientLight.h"

namespace MrKWatkins::Rendering::Scene
{
    AmbientLight::AmbientLight(Rendering::Colour colour) : Light(colour)
    {
    }

    Geometry::Vector AmbientLight::GetDirectionAtPoint(Geometry::Point point, Geometry::Vector surfaceNormal) const
    {
        return surfaceNormal;
    }
}
