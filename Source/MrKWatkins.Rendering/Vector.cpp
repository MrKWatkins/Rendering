#include "stdafx.h"
#include "Vector.h"
#include <stdexcept>
#include <sstream>

namespace MrKWatkins::Rendering::Geometry
{
    Vector::Vector(double x, double y, double z) : x{ x }, y{ y }, z{ z }
    {
    }

    double Vector::Length() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    Vector Vector::operator+(const Vector& other) const
    {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    Vector Vector::operator-(const Vector& other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    Vector Vector::operator-() const
    {
        return Vector(-x, -y, -z);
    }

    Vector Vector::operator*(double scalar) const
    {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator*(double scalar, const Vector& vector)
    {
        return vector * scalar;
    }

    Vector Vector::operator/(double scalar) const
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("scalar cannot be 0.");
        }
        return Vector(x / scalar, y / scalar, z / scalar);
    }

    double Vector::Dot(const Vector& other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    Vector Vector::Cross(const Vector& other) const
    {
        return Vector(
            y*other.z - z*other.y,
            z*other.x - x*other.z,
            x*other.y - y*other.x);
    }

    Vector Vector::Normalize() const
    {
        const auto multiplier = 1.0 / Length();

        return Vector(x * multiplier, y * multiplier, z * multiplier);
    }

    std::string Vector::ToString() const
    {
        std::ostringstream oss;
        oss << "(" << x << "," << y << "," << z << ")";
        return oss.str();
    }

    std::ostream& operator<<(std::ostream& os, const Vector& vector)
    {
        os << vector.ToString();
        return os;
    }
}
