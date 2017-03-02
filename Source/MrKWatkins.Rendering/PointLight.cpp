#include "stdafx.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Scene
{
    PointLight::PointLight(Rendering::Colour colour, Geometry::Point position): Light(colour), position { position}
    {
    }

    Geometry::Vector PointLight::GetDirectionAtPoint(Geometry::Point point, Geometry::Vector surfaceNormal) const
    {
        return position - point;
    }
}
