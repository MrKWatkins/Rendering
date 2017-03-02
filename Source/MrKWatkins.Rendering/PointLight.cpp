#include "stdafx.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Scene
{
    PointLight::PointLight(Rendering::Colour colour, Geometry::Point position): Light(colour), position { position}
    {
    }

    Geometry::Ray PointLight::GetLightRayToPoint(Geometry::Point point) const
    {
        return Geometry::Ray(position, point - position);
    }
}
