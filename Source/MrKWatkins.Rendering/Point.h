#pragma once
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// An immutable point in three-dimensions.
    /// </summary>
    class Point final
    {
        double x;
        double y;
        double z;
    public:
        Point() = default;
        Point(double x, double y, double z);

        double X() const noexcept { return x; }
        double Y() const noexcept { return y; }
        double Z() const noexcept { return z; }

        Point operator+(const Vector& vector) const;
        Vector operator-(const Point& other) const;

		bool operator==(const Point& other) const;
		bool operator!=(const Point& other) const;

		double operator [](unsigned int index) const;

        double DistanceFrom(const Point& other) const;

        std::string ToString() const;
        friend std::ostream& operator<<(std::ostream& os, const Point& point);

		static const Point& Origin() noexcept;
    };
}
