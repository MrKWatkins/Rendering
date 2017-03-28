#pragma once
#include <random>
#include "Vector.h"
#include "Point.h"

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