#pragma once

namespace MrKWatkins::Rendering::Geometry
{
    struct Point
    {
    private:
        double x;
        double y;
        double z;
    public:
        Point() = default;
        Point(double x, double y, double z);

        double X() const noexcept { return x; }
        double Y() const noexcept { return y; }
        double Z() const noexcept { return z; }
    };
}
