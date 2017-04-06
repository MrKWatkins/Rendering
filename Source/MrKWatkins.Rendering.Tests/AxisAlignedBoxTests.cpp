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

		// TODO: Same tests for y, x axes. Can we pull out the test code and use axis indexers to share code?
		SECTION("Outside box with rays parallel to the x-axis")
		{
			// Create an origin that will hit the box with direction in positive X. Position X before the near side and position y and z in the boundaries of the box.
			auto rayOriginX = nearCorner.X() - Random::GreaterThanZero();

			// Box in front on x-axis, outside of box in y-axis.
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, box.Maximum().Y() + Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, box.Minimum().Y() - Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());

			// Box in front on x-axis, outside of box in z-axis.
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Maximum().Z() + Random::GreaterThanZero()), Vector::I())).has_value());
			CHECK(!box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Minimum().Z() - Random::GreaterThanZero()), Vector::I())).has_value());

			// Box in front on x-axis.
			auto result = box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));

			// Box behind on x-axis.
			CHECK(!box.NearestIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), Vector::I())).has_value());

			// Box behind on x-axis, ray pointing backwards.
			result = box.NearestIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(Vector::I()));
		}

		SECTION("Inside box with rays parallel to the x-axis")
		{
			// Facing maximum side.
			auto result = box.NearestIntersection(Ray(pointInside, Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));

			// Facing minimum side.
			result = box.NearestIntersection(Ray(pointInside, -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(Vector::I()));

			// On minimum side, facing maximum side - intersection should be with the maximum side and not the side we're overlapping.
			result = box.NearestIntersection(Ray(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));

			// On maximum side, facing minimum side - intersection should be with the minimum side and not the side we're overlapping.
			result = box.NearestIntersection(Ray(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result.value().Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result.value().SurfaceNormal(), Equals(Vector::I()));
		}
	}

	TEST_CASE("AxisAlignedBox - Bug", "[AxisAlignedBox]")
	{
		auto box = AxisAlignedBox(Point(0.1, 0.9, 0.1), 0.8, 0.1, 1);
		auto ray = Ray(Point(0.1, 1, 0.42551694027005382), Vector(0.20333247500773682, 0.25416559375967102, 0.94554521602936681));

		auto intersection = box.NearestIntersection(ray);
	}
}