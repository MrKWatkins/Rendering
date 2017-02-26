#pragma once

namespace MrKWatkins::Rendering::Geometry
{
    struct Vector
    {
    private:
        double x;
        double y;
        double z;
    public:
        Vector() = default;
        Vector(double x, double y, double z);

        double X() const noexcept { return x; }
        double Y() const noexcept { return y; }
        double Z() const noexcept { return z; }

        Vector operator+(const Vector& other) const;
    };
}
