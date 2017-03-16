#include "stdafx.h"
#include "Gradient.h"

namespace MrKWatkins::Rendering::Algorithms
{
    Gradient::Gradient() : Gradient(Colour(0, 0, 0), Colour(1, 1, 1))
    {
    }

    Gradient::Gradient(Colour from, Colour to) : from{ from }, to{ to }
    {
    }

    Colour Gradient::RenderPoint(double x, double y) const
    {
        return Colour(
            Interpolate(from.R(), to.R(), x * y),
            Interpolate(from.G(), to.G(), x * y),
            Interpolate(from.B(), to.B(), x * y));
    }

    double Gradient::Interpolate(double from, double to, double position)
    {
        return from + position * (to - from);
    }
}
