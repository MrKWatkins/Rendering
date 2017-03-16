#include "stdafx.h"
#include "Random.h"

namespace MrKWatkins::Rendering::Algorithms
{
    Random::Random() : Random(std::random_device{}())
    {
    }

    Random::Random(unsigned int seed) : generator{ seed }
    {
    }

    Colour Random::RenderPoint(double x, double y) const
    {
        return Colour{ distribution(generator),  distribution(generator),  distribution(generator) };
    }
}
