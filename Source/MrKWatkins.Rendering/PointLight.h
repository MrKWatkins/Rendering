#pragma once
#include "Light.h"
#include "Point.h"
#include "Colour.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Lighting
{
    class PointLight final : public Light
    {
        Point position;
    public:
        PointLight(const Rendering::Colour& colour, const Attenuation& attenuation, const Point& position);

        Ray GetRayToPoint(const Point& point) const override;

        double GetIntensityAtPoint(const Point& point) const override;
    };
}
