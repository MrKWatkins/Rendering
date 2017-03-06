#pragma once
#include "Light.h"
#include "Point.h"
#include "Colour.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Lighting
{
    class PointLight : public Light
    {
        Point position;
    public:
        PointLight(const Rendering::Colour& colour, const Attenuation& attenuation, const Point& position);

        Ray GetLightRayToPoint(const Point& point) const override;

        double GetIntensityAtPoint(const Point& point) const override;
    };
}
