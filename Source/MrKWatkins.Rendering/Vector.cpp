#include "stdafx.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Geometry
{
    Vector::Vector(double x, double y, double z) : x{ x }, y{ y }, z{ z }
    {
    }

    Vector Vector::operator+(const Vector& other) const
    {
        return Vector(x + other.x, y + other.y, z + other.z);
    }
}
