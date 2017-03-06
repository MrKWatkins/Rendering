#pragma once
#include "Colour.h"
#include "Ray.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Lighting
{
    class Light
    {
    protected:
        Colour colour;
        explicit Light(const Colour& colour);
    public:
        virtual ~Light() = default;

        virtual Ray GetLightRayToPoint(const Point& point) const = 0;

        const Colour& Colour() const noexcept { return colour; }
    };
}
