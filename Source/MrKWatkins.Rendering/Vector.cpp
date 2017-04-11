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
		VERIFY_IS_FINITE(x);
		VERIFY_IS_FINITE(y);
		VERIFY_IS_FINITE(z);
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
		VERIFY_IS_FINITE(scalar);

        return Vector(x * scalar, y * scalar, z * scalar);
    }

    Vector operator*(double scalar, const Vector& vector)
    {
		VERIFY_IS_FINITE(scalar);

        return vector * scalar;
    }

	Vector Vector::operator/(double scalar) const
	{
		VERIFY_IS_FINITE(scalar);

		// Don't use VERIFY_NOT_ZERO as that is a tolerance comparison which the compiler doesn't know about, causing us to get a C4273 'potential divide by 0'.
		if (scalar == 0)
		{
			throw std::invalid_argument("scalar cannot be zero.");
		}
		return Vector(x / scalar, y / scalar, z / scalar);
	}

	double Vector::operator[](unsigned int index) const
	{
		switch (index)
		{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
		}

		throw std::out_of_range("index equals " + std::to_string(index) + " which is not in the range 0 -> 2.");
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

	const Vector& Vector::Axis(unsigned int index)
	{
		switch (index)
		{
		case 0:
			return I();
		case 1:
			return J();
		case 2:
			return K();
		}

		throw std::out_of_range("index equals " + std::to_string(index) + " which is not in the range 0 -> 2.");
	}

	Vector Vector::ReflectAboutNormal(const Vector& vectorPointingToNormal, const Vector& normal)
	{
		VERIFY_IS_NORMALIZED(normal);

		// TODO: Is result normalized if vectorPointingToNormal is normalized?
		return 2 * vectorPointingToNormal.Dot(normal) * normal - vectorPointingToNormal;
	}
}
