#include "stdafx.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Lighting
{
    PointLight::PointLight(const Rendering::Colour& colour, const Point& position): Light(colour), position { position}
    {
    }

    Ray PointLight::GetLightRayToPoint(const Point& point) const
    {
        // point - position => gives the vector that if we added to position, i.e. where our light is, it would take us to the point.
        return Ray(position, point - position);
    }
}
