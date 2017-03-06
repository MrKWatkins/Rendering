#include "stdafx.h"
#include "Point.h"
#include "Colour.h"
#include "SkyGradient.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Materials
{
    SkyGradient::SkyGradient(const Colour& horizonColour, const Colour& zenithColour) : horizonColour{ horizonColour }, zenithColour { zenithColour }
    {
    }

    Colour SkyGradient::GetColourAtPoint(const Point& point) const
    {
        // Could make this more generic by allowing the user to specify the gradient direction.
        return Colour::Interpolate(horizonColour, zenithColour, abs(Vector::J().Dot(Vector(point).Normalize())));
    }
}