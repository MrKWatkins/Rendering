#pragma once
#include "Colour.h"
#include "Ray.h"

namespace MrKWatkins::Rendering::Scene
{
    class Light
    {
    protected:
        Colour colour;
        explicit Light(const Colour& colour);
    public:
        virtual ~Light() = default;

        virtual Geometry::Ray GetLightRayToPoint(const Geometry::Point& point) const = 0;

        const Colour& Colour() const noexcept { return colour; }
    };
}
