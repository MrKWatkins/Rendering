#include "stdafx.h"
#include <random>
#include <Vector.h>
#include <Point.h>
#include "Random.h"

namespace MrKWatkins::Rendering::Tests::Random
{
    auto generator = std::default_random_engine{ std::random_device{}() };

    double Double()
    {
		static const auto distribution = std::uniform_real_distribution<double>{ -1000, 1000 };

        return distribution(generator);
    }

	double Range(double minimum, double maximum)
	{
		auto distribution = std::uniform_real_distribution<double>{ minimum, maximum };

		return distribution(generator);
	}

	double Positive()
    {
		static const auto distribution = std::uniform_real_distribution<double>{ 0, 1000 };

        return distribution(generator);
    }

	double GreaterThanZero()
	{
		static const auto distribution = std::uniform_real_distribution<double>{ 0.001, 1000 };

		return distribution(generator);
	}

	double Negative()
	{
		return -Positive();
	}

	double LessThanZero()
	{
		return -GreaterThanZero();
	}

	double ZeroToOne()
	{
		static const auto distribution = std::uniform_real_distribution<double>{ 0, 1 };

		return distribution(generator);
	}

	Geometry::Vector Vector()
    {
        return Geometry::Vector(Double(), Double(), Double());
    }

    Geometry::Point Point()
    {
        return Geometry::Point(Double(), Double(), Double());
    }

	Geometry::Point PointInside(const Geometry::AxisAlignedBox& box)
	{
		return Geometry::Point(
			Range(box.Minimum().X(), box.Maximum().X()),
			Range(box.Minimum().Y(), box.Maximum().Y()),
			Range(box.Minimum().Z(), box.Maximum().Z()));
	}
}
