#include "stdafx.h"
#include <random>
#include "Vector.h"
#include "Point.h"
#include "Random.h"

namespace MrKWatkins::Rendering::Tests
{
    std::default_random_engine Random::generator = std::default_random_engine{ std::random_device{}() };
    std::uniform_real_distribution<double> Random::distribution = std::uniform_real_distribution<double>{ 0, 100 };

    double Random::Double()
    {
        return distribution(generator);
    }

    Geometry::Vector Random::Vector()
    {
        return Geometry::Vector(Double(), Double(), Double());
    }

    Geometry::Point Random::Point()
    {
        return Geometry::Point(Double(), Double(), Double());
    }
}
