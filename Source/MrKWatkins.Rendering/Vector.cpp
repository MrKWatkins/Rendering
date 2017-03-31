#include "stdafx.h"
#include "Verify.h"
#include "Vector.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Geometry
{
	Vector::Vector(double x, double y, double z, bool isNormalized) : x{ x }, y{ y }, z{ z }, isNormalized{ isNormalized }
	{
	}

	Vector::Vector(double x, double y, double z) : Vector(x, y, z, false)
	{
		Verify::ValidNumber(x, "x");
		Verify::ValidNumber(y, "y");
		Verify::ValidNumber(z, "z");
	}

    Vector::Vector(const Point& point) : Vector(point.X(), point.Y(), point.Z())
    {
    }

	double Vector::LengthSquared() const
	{
		return x*x + y*y + z*z;
	}

	double Vector::Length() const
	{
		return sqrt(LengthSquared());
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

		// TODO: Quicker to invert then multiply?
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
		if (isNormalized)
		{
			return *this;
		}

        const auto length = Length();
        if (length == 0)
        {
            return Zero();
        }

        const auto multiplier = 1.0 / length;

        return Vector(x * multiplier, y * multiplier, z * multiplier, true);
    }

	Vector Vector::ReflectAbout(const Vector& normal) const
	{
		Verify::IsNormalized(normal, "normal");

		return 2 * Dot(normal) * normal - *this;
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
		static const auto zero = Vector(0, 0, 0, false);

		return zero;
	}

	const Vector& Vector::I() noexcept
	{
		static const auto i = Vector(1, 0, 0, true);

		return i;
	}

	const Vector& Vector::J() noexcept
	{
		static const auto j = Vector(0, 1, 0, true);

		return j;
	}

	const Vector& Vector::K() noexcept
	{
		static const auto k = Vector(0, 0, 1, true);

		return k;
	}
}
