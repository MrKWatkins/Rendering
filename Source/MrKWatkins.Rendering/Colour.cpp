#include "stdafx.h"
#include "Colour.h"
#include <algorithm>

namespace MrKWatkins::Rendering
{
    // TODO: Parameter validation OR clamp.
    Colour::Colour(double r, double g, double b) : r{ r }, g{ g }, b{ b }
    {
    }

    Colour Colour::operator*(const Colour& colour) const
    {
        return Colour(r * colour.r, g * colour.g, b * colour.b);
    }

    Colour Colour::operator+(const Colour& colour) const
    {
        return Colour(std::clamp(r + colour.r, 0.0, 1.0), std::clamp(g + colour.g, 0.0, 1.0), std::clamp(b + colour.b, 0.0, 1.0));
    }

    Colour Colour::operator*(double multiple) const
    {
        auto multiplier = std::clamp(multiple, 0.0, 1.0);

        return Colour(r * multiplier, g * multiplier, b * multiplier);
    }

    Colour operator*(double multiple, const Colour& colour)
    {
        return colour * multiple;
    }

    double InterpolateComponent(double from, double to, double position)
    {
        return from + position * (to - from);
    }

    Colour Colour::Interpolate(const Colour& from, const Colour& to, double position)
    {
        position = std::clamp(position, 0.0, 1.0);

        return Colour(
            InterpolateComponent(from.R(), to.R(), position),
            InterpolateComponent(from.G(), to.G(), position),
            InterpolateComponent(from.B(), to.B(), position));
    }	

	const Colour& Colour::Black() noexcept
	{
		static auto black = Colour(0, 0, 0);

		return black;
	}

	const Colour& Colour::White() noexcept
	{
		static auto white = Colour(1, 1, 1);

		return white;
	}
}
