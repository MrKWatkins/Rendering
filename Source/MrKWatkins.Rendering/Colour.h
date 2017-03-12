#pragma once

namespace MrKWatkins::Rendering
{
    class Colour final
    {
		static Colour black;
		static Colour white;
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

        static Colour Interpolate(const Colour& from, const Colour& to, double position);

		static const Colour& Black() noexcept { return black; }
		static const Colour& White() noexcept { return white; }
    };
}
