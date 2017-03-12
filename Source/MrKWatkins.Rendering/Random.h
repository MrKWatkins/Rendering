#pragma once
#include "Algorithm.h"
#include <random>

namespace MrKWatkins::Rendering::Algorithms
{
    class Random final : public Algorithm
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution{ 0, 1 };
    public:
        Random();
        explicit Random(unsigned int seed);

        ~Random() = default;

        Colour RenderPoint(double x, double y) override;
    };
}
