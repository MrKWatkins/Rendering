#pragma once

namespace MrKWatkins::Rendering
{
    class Colour
    {
        double r;
        double g;
        double b;
    public:
        Colour() = default; 
        Colour(double r, double g, double b);

        Colour operator*(const Colour& colour) const;
        Colour operator+(const Colour& colour) const;

        Colour operator*(double multiple) const;
        friend Colour operator*(double multiple, const Colour& colour);

        double R() const noexcept { return r; }
        double G() const noexcept { return g; }
        double B() const noexcept { return b; }
    };
}
