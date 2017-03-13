#include "stdafx.h"
#include "Point.h"
#include "Colour.h"
#include "SkyGradient.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Textures
{
    SkyGradient::SkyGradient(const Colour& horizonColour, const Colour& zenithColour) : horizonColour{ horizonColour }, zenithColour { zenithColour }
    {
    }

	Material SkyGradient::GetMaterialAtPoint(const Point& point) const
    {
        // Could make this more generic by allowing the user to specify the gradient direction.
        return Material(Colour::Interpolate(horizonColour, zenithColour, abs(Vector::J().Dot(Vector(point).Normalize()))));
    }
}