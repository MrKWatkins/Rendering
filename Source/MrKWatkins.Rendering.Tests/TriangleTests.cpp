#include "stdafx.h"
#include <Triangle.h>
#include "catch.hpp"
#include "Matchers.h"
#include "Random.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::TriangleTests
{
	auto corner0 = Random::Point();
	auto corner1 = Random::Point();
	auto corner2 = Random::Point();
	auto triangle = Triangle(corner0, corner1, corner2);

	TEST_CASE("Triangle - Single triangle iterator", "[Triangle]")
	{
		std::vector<Point> points;

		for (auto& point : triangle)
		{
			points.push_back(point);
		}

		CHECK_THAT(points[0], Equals(corner0));
		CHECK_THAT(points[1], Equals(corner1));
		CHECK_THAT(points[2], Equals(corner2));
	}
}