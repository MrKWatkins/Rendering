#pragma once
#include "Colour.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Scene
{
    class Light
    {
    protected:
        Colour colour;
        explicit Light(Colour colour);
    public:
        virtual ~Light() = default;

        virtual Geometry::Vector GetDirectionAtPoint(Geometry::Point point) const = 0;

        Colour Colour() const { return colour; }
    };
}
