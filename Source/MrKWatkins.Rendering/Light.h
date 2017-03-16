#pragma once
#include "Colour.h"
#include "Ray.h"
#include "Attenuation.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Lighting
{
    class Light
    {
    protected:
        Colour colour;
        Attenuation attenuation;
        Light(const Colour& colour, const Attenuation& attenuation);
    public:
        virtual ~Light() = default;

		/// <summary>
		/// Returns a ray from the light to the specified point.
		/// </summary>
        virtual Ray GetRayToPoint(const Point& point) const = 0;

        virtual double GetIntensityAtPoint(const Point& point) const = 0;

        const Colour& Colour() const noexcept { return colour; }
    };
}
