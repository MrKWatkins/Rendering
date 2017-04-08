#include "stdafx.h"
#include "Doubles.h"
#include "Point.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
    Point::Point(double x, double y, double z) : x{ x }, y{ y }, z{ z }
    {
		VERIFY_IS_FINITE(x);
		VERIFY_IS_FINITE(y);
		VERIFY_IS_FINITE(z);
    }

    Point Point::operator+(const Vector& vector) const
    {
        return Point(x + vector.X(), y + vector.Y(), z + vector.Z());
    }

    Vector Point::operator-(const Point& other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

	bool Point::operator==(const Point& other) const
	{
		return Doubles::AreEqual(x, other.x) && Doubles::AreEqual(y, other.y) && Doubles::AreEqual(z, other.z);
	}

	bool Point::operator!=(const Point& other) const
	{
		return !(*this == other);
	}

	double Point::operator[](unsigned int index) const
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

	double Point::DistanceFrom(const Point& other) const
    {
        return (*this - other).Length();
    }

    std::string Point::ToString() const
    {
        std::ostringstream oss;
        oss << "Point (" << x + 0.0 << "," << y + 0.0 << "," << z + 0.0 << ")";   // + 0.0 converts -0.0 into +0.0.
        return oss.str();
    }

	std::ostream& operator<<(std::ostream& os, const Point& point)
    {
        os << point.ToString();
        return os;
    }

	const Point& Point::Origin() noexcept
	{
		static auto origin = Point(0, 0, 0);

		return origin;
	}
}
