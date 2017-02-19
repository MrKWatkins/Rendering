#include "stdafx.h"
#include "RandomAlgorithm.h"

namespace MrKWatkins::Rendering
{
    RandomAlgorithm::RandomAlgorithm() : generator({ std::random_device{}() })
    {
    }

    RandomAlgorithm::RandomAlgorithm(double seed) : generator(seed)
    {
    }

    Colour RandomAlgorithm::RenderPoint(double x, double y)
    {
        return Colour{ distribution(generator),  distribution(generator),  distribution(generator) };
    }
}
