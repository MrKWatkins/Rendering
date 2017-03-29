#include "stdafx.h"
#include <Sphere.h>
#include "catch.hpp"
#include "Random.h"
#include "Matchers.h"
#include <functional>

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::PointTests
{
    TEST_CASE("Sphere - NearestIntersection - sphere behind ray", "[Sphere]")
    {
        // Sphere centered at point on negative x-axis with radius less than distance along x-axis so sphere entirely in negative x.
        // No intersection with ray along positive x-axis.
        auto radius = Random::Double();
        auto xOrigin = -Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector::I()));
        REQUIRE(!result.has_value());
    }

    TEST_CASE("Sphere - NearestIntersection - sphere in front of ray", "[Sphere]")
    {
        // Sphere centered at point on x-axis with radius less than distance along x-axis so sphere entirely in positive x.
        // Intersection with ray along x-axis will be at origin - radius on x-axis.
        // Surface normal will be pointing along negative x.
        auto radius = Random::Double();
        auto xOrigin = Random::Double() * radius;
        auto result = Sphere(Point(xOrigin, 0, 0), radius).NearestIntersection(Ray(Point::Origin(), Vector::I()));
        REQUIRE(result.has_value());
        CHECK_THAT(result.value().Point(), Equals(Point(xOrigin - radius, 0, 0)));
        CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));
    }

	TEST_CASE("Sphere - NearestIntersection - ray hits sphere at tangent", "[Sphere]")
	{
		// Sphere centered on origin. Ray starts from behind the y-axis, pointing into positive x. Starts radius along y so it strikes the sphere at the tangent.
		// Intersection will be radius along y. Surface normal will point along y.
		auto radius = Random::Double();
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(Point(-radius, radius, 0), Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(0, radius, 0)));
		CHECK_THAT(result.value().SurfaceNormal(), Equals(Vector::J()));
	}

	void RayInsideSphere(std::function<double(double)> rayOriginOnXAxisFromRadius)
    {
		auto radius = Random::Double();
		auto result = Sphere(Point::Origin(), radius).NearestIntersection(Ray(Point(rayOriginOnXAxisFromRadius(radius), 0, 0), Vector::I()));
		REQUIRE(result.has_value());
		CHECK_THAT(result.value().Point(), Equals(Point(radius, 0, 0)));	// Intersection will be at the sphere's radius on the x axis.
		CHECK_THAT(result.value().SurfaceNormal(), Equals(-Vector::I()));	// As we're inside the normal points back towards us.
    }

    TEST_CASE("Sphere - NearestIntersection - ray inside spherewith ray origin equidistant between intersections", "[Sphere]")
    {
		RayInsideSphere([](double radius) { return 0; });
    }

	TEST_CASE("Sphere - NearestIntersection - ray inside sphere with closest intersection behind ray origin", "[Sphere]")
	{
		RayInsideSphere([](double radius) { return 0 - radius / 2; });
	}

	TEST_CASE("Sphere - NearestIntersection - ray inside sphere with closest intersection in front of ray origin", "[Sphere]")
	{
		RayInsideSphere([](double radius) { return radius / 2; });
	}

	TEST_CASE("Sphere - NearestIntersection - ray inside sphere with ray origin on one intersection", "[Sphere]")
	{
		RayInsideSphere([](double radius) { return -radius; });
	}
}