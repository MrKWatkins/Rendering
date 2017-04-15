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
			CHECK(box.NearestIntersection(Ray(Point(rayOriginX, box.Maximum().Y() + Random::GreaterThanZero(), pointInside.Z()), Vector::I())) == nullptr);
			CHECK(box.NearestIntersection(Ray(Point(rayOriginX, box.Minimum().Y() - Random::GreaterThanZero(), pointInside.Z()), Vector::I())) == nullptr);

			// Box in front on x-axis, outside of box in z-axis.
			CHECK(box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Maximum().Z() + Random::GreaterThanZero()), Vector::I())) == nullptr);
			CHECK(box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), box.Minimum().Z() - Random::GreaterThanZero()), Vector::I())) == nullptr);

			// Box in front on x-axis.
			auto inFront = box.NearestIntersection(Ray(Point(rayOriginX, pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(inFront != nullptr);
			CHECK_THAT(inFront->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(inFront->Normal(), Equals(-Vector::I()));

			// Box behind on x-axis.
			CHECK(box.NearestIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), Vector::I())) == nullptr);

			// Box behind on x-axis, ray pointing backwards.
			auto behind = box.NearestIntersection(Ray(Point(box.Maximum().X() + Random::GreaterThanZero(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(behind != nullptr);
			CHECK_THAT(behind->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(behind->Normal(), Equals(Vector::I()));
		}

		SECTION("Inside box with rays parallel to the x-axis")
		{
			// Facing maximum side.
			auto facingMax = box.NearestIntersection(Ray(pointInside, Vector::I()));
			REQUIRE(facingMax != nullptr);
			CHECK_THAT(facingMax->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(facingMax->Normal(), Equals(-Vector::I()));

			// Facing minimum side.
			auto facingMin = box.NearestIntersection(Ray(pointInside, -Vector::I()));
			REQUIRE(facingMin != nullptr);
			CHECK_THAT(facingMin->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(facingMin->Normal(), Equals(Vector::I()));

			// On minimum side, facing maximum side - intersection should be with the maximum side and not the side we're overlapping.
			auto onMinFacingMax = box.NearestIntersection(Ray(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z()), Vector::I()));
			REQUIRE(onMinFacingMax != nullptr);
			CHECK_THAT(onMinFacingMax->Point(), Equals(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(onMinFacingMax->Normal(), Equals(-Vector::I()));

			// On maximum side, facing minimum side - intersection should be with the minimum side and not the side we're overlapping.
			auto onMaxFacingMin = box.NearestIntersection(Ray(Point(box.Maximum().X(), pointInside.Y(), pointInside.Z()), -Vector::I()));
			REQUIRE(onMaxFacingMin != nullptr);
			CHECK_THAT(onMaxFacingMin->Point(), Equals(Point(box.Minimum().X(), pointInside.Y(), pointInside.Z())));
			CHECK_THAT(onMaxFacingMin->Normal(), Equals(Vector::I()));
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