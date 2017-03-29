#include "stdafx.h"
#include <Sphere.h>
#include "catch.hpp"
#include "Random.h"
#include "Matchers.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::PointTests
{
	// TODO: Tests for intersection at tangent, inside sphere opposite direction, ray origin on intersection.
    TEST_CASE("Sphere - NearestIntersection - sphere behind ray", "[Sphere]")
    {
        // Sphere centered at point on negative x-axis with radius less than distance along x-axis so sphere entirely in negative x.
        // No intersection with ray along positive x-axis.
        auto radius = Random::Double();
        auto xOrigin = -Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector(1, 0, 0)));
        REQUIRE(!result.has_value());
    }

    TEST_CASE("Sphere - NearestIntersection - ray and sphere on x axis", "[Sphere]")
    {
        // Sphere centered at point on x-axis with radius less than distance along x-axis so sphere entirely in positive x.
        // Intersection with ray along x-axis will be at origin - radius on x-axis.
        // Surface normal will be pointing along negative x.
        auto radius = Random::Double();
        auto xOrigin = Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector(1, 0, 0)));
        REQUIRE(result.has_value());
        CHECK_THAT(result.value().Point(), Equals(Point(xOrigin - radius, 0, 0)));
        CHECK_THAT(result.value().SurfaceNormal(), Equals(Vector(-1, 0, 0)));
    }

	// TODO: Share code - one test.
    TEST_CASE("Sphere - NearestIntersection - ray inside sphere equidistant between intersections", "[Sphere]")
    {
        auto radius = Random::Double();
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(Point::Origin(), Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(radius, 0, 0)));	// Intersection will be at the sphere's radius on the x axis.
		CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));	// As we're inside the normal points back towards us.
    }

	TEST_CASE("Sphere - NearestIntersection - ray inside sphere with closest intersection behind", "[Sphere]")
	{
		auto radius = Random::Double();
		auto rayOrigin = Point(0 - radius / 2, 0, 0);	// Start it behind the origin but still inside the sphere.
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(rayOrigin, Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(radius, 0, 0)));	// Intersection will be at the sphere's radius on the x axis.
		CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));	// As we're inside the normal points back towards us.
	}

	TEST_CASE("Sphere - NearestIntersection - ray inside sphere with closest intersection in front", "[Sphere]")
	{
		auto radius = Random::Double();
		auto rayOrigin = Point(radius / 2, 0, 0);	// Start it in front of the origin but still inside the sphere.
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(rayOrigin, Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(radius, 0, 0)));	// Intersection will be at the sphere's radius on the x axis.
		CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));	// As we're inside the normal points back towards us.
	}

	TEST_CASE("Sphere - NearestIntersection - ray starts on one intersection", "[Sphere]")
	{
		auto radius = Random::Double();
		auto rayOrigin = Point(0 - radius, 0, 0);
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(rayOrigin, Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(radius, 0, 0)));	// Intersection will be at the sphere's radius on the x axis.
		CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));	// As we're inside the normal points back towards us.
	}
}