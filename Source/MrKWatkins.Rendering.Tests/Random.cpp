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
		static const auto doubleDistribution = std::uniform_real_distribution<double>{ -1000, 1000 };

        return doubleDistribution(generator);
    }

	double Range(double minimum, double maximum)
	{
		auto rangeDistribution = std::uniform_real_distribution<double>{ minimum, maximum };

		return rangeDistribution(generator);
	}

	double Positive()
    {
		static const auto positiveDistribution = std::uniform_real_distribution<double>{ 0, 1000 };

        return positiveDistribution(generator);
    }

	double GreaterThanZero()
	{
		static const auto greaterThanZeroDistribution = std::uniform_real_distribution<double>{ 0.001, 1000 };

		return greaterThanZeroDistribution(generator);
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
		static const auto zeroToOneDistribution = std::uniform_real_distribution<double>{ 0, 1 };

		return zeroToOneDistribution(generator);
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
