#pragma once

namespace MrKWatkins::Rendering
{
    struct Colour
    {
    private:
        double r;
        double g;
        double b;
    public:
        Colour() = default; 
        Colour(double r, double g, double b);

        double R() const noexcept { return r; }
        double G() const noexcept { return g; }
        double B() const noexcept { return b; }
    };
}
