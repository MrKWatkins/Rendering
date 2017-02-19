#pragma once
#include "Algorithm.h"
#include <random>

namespace MrKWatkins::Rendering
{
    class RandomAlgorithm : public Algorithm
    {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution{ 0, 1 };
    public:
        RandomAlgorithm();
        explicit RandomAlgorithm(double seed);

        Colour RenderPoint(double x, double y) override;

        ~RandomAlgorithm() = default;
    };
}
