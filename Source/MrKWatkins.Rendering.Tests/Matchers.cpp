#include "stdafx.h"
#include "Vector.h"
#include "Point.h"
#include "Matchers.h"

namespace MrKWatkins::Rendering::Tests
{
	VectorEquals::VectorEquals(Geometry::Vector const& vector) : vector{ vector }
	{
	}

	VectorEquals::VectorEquals(VectorEquals const& other) : vector{ other.vector }
	{
	}

	bool VectorEquals::match(Geometry::Vector const& other) const
	{
		return vector.X() == Approx(other.X()) &&
			vector.Y() == Approx(other.Y()) &&
			vector.Z() == Approx(other.Z());
	}

	std::string VectorEquals::describe() const
	{
		return "equals " + vector.ToString();
	}

	PointEquals::PointEquals(Geometry::Point const& point) : point{ point }
	{
	}

	PointEquals::PointEquals(PointEquals const& other) : point{ other.point }
	{
	}

	bool PointEquals::match(Geometry::Point const& other) const
	{
		return point.X() == Approx(other.X()) &&
			point.Y() == Approx(other.Y()) &&
			point.Z() == Approx(other.Z());
	}

	std::string PointEquals::describe() const
	{
		return "equals " + point.ToString();
	}
}
