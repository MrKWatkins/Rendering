#pragma once
#include "Colour.h"
#include "Algorithm.h"

namespace MrKWatkins::Rendering::Algorithms
{
    class Gradient final : public Algorithm
    {
        Colour from;
        Colour to;

        static double Interpolate(double from, double to, double position);

    public:
        Gradient();
        explicit Gradient(Colour from, Colour to);

        ~Gradient() = default;

        Colour RenderPoint(double x, double y) override;
    };
}
