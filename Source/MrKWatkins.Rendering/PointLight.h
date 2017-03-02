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
        PointLight(Rendering::Colour colour, Geometry::Point position);

        Geometry::Vector GetDirectionAtPoint(Geometry::Point point) const override;
    };
}
