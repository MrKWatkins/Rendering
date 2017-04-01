#include "stdafx.h"
#include <AxisAlignedBox.h>
#include "catch.hpp"
#include "Random.h"
#include "Matchers.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::AxisAlignedBoxTests
{
	TEST_CASE("AxisAlignedBox - NearestIntersection", "[AxisAlignedBox]")
	{
		auto nearCorner = Random::Point();
		auto width = Random::Positive();
		auto height = Random::Positive();
		auto depth = Random::Positive();
		auto box = AxisAlignedBox(nearCorner, width, height, depth);
		auto pointInside = Random::PointInside(box);

		SECTION("Box in front on x-axis")
		{
			// Create an origin that will hit the box with direction in positive X. Position X before the near side and
			// position y and z in the boundaries of the box.
			auto rayOriginX = nearCorner.X() - Random::GreaterThanZero();

			// Outside of box in y.
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, box.Maximum().Y() + Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, box.Minimum().Y() - Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());

			// Outside of box in z.
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Maximum().Z() + Random::GreaterThanZero()), Vector::I())).has_value());
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Maximum().Z() - Random::GreaterThanZero()), Vector::I())).has_value());

			// Intersecting.
			auto result = box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));
		}

		SECTION("Inside box on x-axis")
		{
		}
		SECTION("Box behind on x-axis")
		{
		}

		// Same for y, z.
	}
}