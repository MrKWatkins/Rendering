#pragma once
#include <random>
#include "../MrKWatkins.Rendering/Vector.h"
#include "../MrKWatkins.Rendering/Point.h"

namespace MrKWatkins::Rendering::Tests
{
    class Random
    {
        static std::default_random_engine generator;
        static std::uniform_real_distribution<double> distribution;
    public:
        static double Double();
        static Geometry::Vector Vector();
        static Geometry::Point Point();
    };
}