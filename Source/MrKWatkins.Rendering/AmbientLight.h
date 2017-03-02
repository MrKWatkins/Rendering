#pragma once
#include "Light.h"
#include "Point.h"
#include "Colour.h"

namespace MrKWatkins::Rendering::Scene
{
    class AmbientLight : public Light
    {
        Geometry::Point position;
    public:
        explicit AmbientLight(Rendering::Colour colour);

        Geometry::Vector GetDirectionAtPoint(Geometry::Point point, Geometry::Vector surfaceNormal) const override;
    };
}
