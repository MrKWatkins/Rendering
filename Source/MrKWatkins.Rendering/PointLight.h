#pragma once
#include "Light.h"
#include "Point.h"
#include "Colour.h"

namespace MrKWatkins::Rendering::Scene
{
    class PointLight : public Light
    {
        Geometry::Point position;
    public:
        PointLight(const Rendering::Colour& colour, const Geometry::Point& position);

        Geometry::Ray GetLightRayToPoint(const Geometry::Point& point) const override;
    };
}
