#include "stdafx.h"
#include "Verify.h"
#include "Vector.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Geometry
{
    Vector::Vector(const Point& point) : x{ point.X() }, y{ point.Y() }, z{ point.Z() }
    {
    }

    Vector::Vector(double x, double y, double z) : x{ x }, y{ y }, z{ z }
    {
		Verify::ValidNumber(x, "x");
		Verify::ValidNumber(y, "y");
		Verify::ValidNumber(z, "z");
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
		Verify::ValidNumber(scalar, "scalar");

        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator*(double scalar, const Vector& vector)
    {
		Verify::ValidNumber(scalar, "scalar");

        return vector * scalar;
    }

    Vector Vector::operator/(double scalar) const
    {
		Verify::ValidNumber(scalar, "scalar");
		Verify::NotZero(scalar, "scalar");

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
        const auto length = Length();
        if (length == 0)
        {
            return Zero();
        }

        const auto multiplier = 1.0 / Length();

        return Vector(x * multiplier, y * multiplier, z * multiplier);
    }

    std::string Vector::ToString() const
    {
        std::ostringstream oss;
        oss << "Vector (" << x + 0.0 << "," << y + 0.0 << "," << z + 0.0 << ")";   // + 0.0 converts -0.0 into +0.0.
        return oss.str();
    }

	std::ostream& operator<<(std::ostream& os, const Vector& vector)
    {
        os << vector.ToString();
        return os;
    }

	const Vector& Vector::Zero() noexcept
	{
		static auto zero = Vector(0, 0, 0);

		return zero;
	}

	const Vector& Vector::I() noexcept
	{
		static auto i = Vector(1, 0, 0);

		return i;
	}

	const Vector& Vector::J() noexcept
	{
		static auto j = Vector(0, 1, 0);

		return j;
	}

	const Vector& Vector::K() noexcept
	{
		static auto k = Vector(0, 0, 1);

		return k;
	}
}
