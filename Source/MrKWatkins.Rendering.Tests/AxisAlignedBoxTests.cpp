#include "stdafx.h"
#include <AxisAlignedBox.h>
#include "catch.hpp"
#include "Random.h"
#include "Matchers.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::AxisAlignedBoxTests
{
	TEST_CASE("AxisAlignedBox - NearestSurfaceIntersection", "[AxisAlignedBox]")
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
			CHECK(!box.NearestSurfaceIntersection(Ray(Point(rayOriginX, box.Maximum().Y() + Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());
			CHECK(!box.NearestSurfaceIntersection(Ray(Point(rayOriginX, box.Minimum().Y() - Random::GreaterThanZero(), pointInside.Z()), Vector::I())).has_value());

			// Box in front on x-axis, outside of box in z-axis.
			CHECK(!box.NearestSurfaceIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Maximum().Z() + Random::GreaterThanZero()), Vector::I())).has_value());
			CHECK(!box.NearestSurfaceIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Minimum().Z() - Random::GreaterThanZero()), Vector::I())).has_value());

			// Box in front on x-axis.
			auto result = box.NearestSurfaceIntersection(Ray(Point(rayOriginX, pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(-Vector::I()));

			// Box behind on x-axis.
			CHECK(!box.NearestSurfaceIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), Vector::I())).has_value());

			// Box behind on x-axis, ray pointing backwards.
			result = box.NearestSurfaceIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(Vector::I()));
		}

		SECTION("Inside box with rays parallel to the x-axis")
		{
			// Facing maximum side.
			auto result = box.NearestSurfaceIntersection(Ray(pointInside, Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(-Vector::I()));

			// Facing minimum side.
			result = box.NearestSurfaceIntersection(Ray(pointInside, -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(Vector::I()));

			// On minimum side, facing maximum side - intersection should be with the maximum side and not the side we're overlapping.
			result = box.NearestSurfaceIntersection(Ray(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(-Vector::I()));

			// On maximum side, facing minimum side - intersection should be with the minimum side and not the side we're overlapping.
			result = box.NearestSurfaceIntersection(Ray(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(result.has_value());
			CHECK_THAT(result->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(result->Normal(), Equals(Vector::I()));
		}
	}

	TEST_CASE("AxisAlignedBox - Width", "[AxisAlignedBox]")
	{
		CHECK(AxisAlignedBox(Point(0, 0, 0), Point(4.5, 0, 0)).Width() == Approx(4.5));
		CHECK(AxisAlignedBox(Point(-4.5, 0, 0), Point(0, 0, 0)).Width() == Approx(4.5));

		CHECK(AxisAlignedBox(Point(2.2, 0, 0), Point(4.5, 0, 0)).Width() == Approx(2.3));
		CHECK(AxisAlignedBox(Point(-4.5, 0, 0), Point(-2.2, 0, 0)).Width() == Approx(2.3));

		CHECK(AxisAlignedBox(Point(-1.3, 0, 0), Point(4.5, 0, 0)).Width() == Approx(5.8));
		CHECK(AxisAlignedBox(Point(-4.5, 0, 0), Point(1.3, 0, 0)).Width() == Approx(5.8));
	}

	TEST_CASE("AxisAlignedBox - Height", "[AxisAlignedBox]")
	{
		CHECK(AxisAlignedBox(Point(0, 0, 0), Point(0, 4.5, 0)).Height() == Approx(4.5));
		CHECK(AxisAlignedBox(Point(0, -4.5, 0), Point(0, 0, 0)).Height() == Approx(4.5));

		CHECK(AxisAlignedBox(Point(0, 2.2, 0), Point(0, 4.5, 0)).Height() == Approx(2.3));
		CHECK(AxisAlignedBox(Point(0, -4.5, 0), Point(0, -2.2, 0)).Height() == Approx(2.3));

		CHECK(AxisAlignedBox(Point(0, -1.3, 0), Point(0, 4.5, 0)).Height() == Approx(5.8));
		CHECK(AxisAlignedBox(Point(0, -4.5, 0), Point(0, 1.3, 0)).Height() == Approx(5.8));
	}

	TEST_CASE("AxisAlignedBox - Depth", "[AxisAlignedBox]")
	{
		CHECK(AxisAlignedBox(Point(0, 0, 0), Point(0, 0, 4.5)).Depth() == Approx(4.5));
		CHECK(AxisAlignedBox(Point(0, 0, -4.5), Point(0, 0, 0)).Depth() == Approx(4.5));

		CHECK(AxisAlignedBox(Point(0, 0, 2.2), Point(0, 0, 4.5)).Depth() == Approx(2.3));
		CHECK(AxisAlignedBox(Point(0, 0, -4.5), Point(0, 0, -2.2)).Depth() == Approx(2.3));

		CHECK(AxisAlignedBox(Point(0, 0, -1.3), Point(0, 0, 4.5)).Depth() == Approx(5.8));
		CHECK(AxisAlignedBox(Point(0, 0, -4.5), Point(0, 0, 1.3)).Depth() == Approx(5.8));
	}
}