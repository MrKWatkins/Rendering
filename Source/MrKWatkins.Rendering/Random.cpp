#include "stdafx.h"
#include "Random.h"

namespace MrKWatkins::Rendering::Algorithms
{
    Random::Random() : Random(std::random_device{}())
    {
    }

    Random::Random(double seed) : generator(seed)
    {
    }

    Colour Random::RenderPoint(double x, double y)
    {
        return Colour{ distribution(generator),  distribution(generator),  distribution(generator) };
    }
}
