#include "stdafx.h"
#include "Point.h"
#include <sstream>

namespace MrKWatkins::Rendering::Geometry
{
    Point Point::origin{ 0, 0, 0 };

    Point::Point(double x, double y, double z) : x{ x }, y{ y }, z{ z }
    {
    }

    Point Point::operator+(const Vector& vector) const
    {
        return Point(x + vector.X(), y + vector.Y(), z + vector.Z());
    }

    Vector Point::operator-(const Point& other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    double Point::DistanceFrom(const Point& other) const
    {
        return (*this - other).Length();
    }

    std::string Point::ToString() const
    {
        std::ostringstream oss;
        oss << "Vector (" << x + 0.0 << "," << y + 0.0 << "," << z + 0.0 << ")";   // + 0.0 converts -0.0 into +0.0.
        return oss.str();
    }

    std::ostream& operator<<(std::ostream& os, const Point& point)
    {
        os << point.ToString();
        return os;
    }
}
