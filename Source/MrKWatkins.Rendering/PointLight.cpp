#include "stdafx.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Scene
{
    PointLight::PointLight(Rendering::Colour colour, Geometry::Point position): Light(colour), position { position}
    {
    }

    Geometry::Ray PointLight::GetLightRayToPoint(Geometry::Point point) const
    {
        // point - position => gives the vector that if we added to position, i.e. where our light is, it would take us to the point.
        return Geometry::Ray(position, point - position);
    }
}
