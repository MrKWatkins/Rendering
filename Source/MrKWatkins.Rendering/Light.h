#pragma once
#include "Colour.h"
#include "Ray.h"

namespace MrKWatkins::Rendering::Scene
{
    class Light
    {
    protected:
        Colour colour;
        explicit Light(Colour colour);
    public:
        virtual ~Light() = default;

        virtual Geometry::Ray GetLightRayToPoint(Geometry::Point point) const = 0;

        Colour Colour() const { return colour; }
    };
}
