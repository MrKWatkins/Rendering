#include "stdafx.h"
#include "catch.hpp"
#include "Random.h"
// TODO: Use include directory to get rid of path.
#include "../MrKWatkins.Rendering/Plane.h"
#include "Matchers.hpp"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::PointTests
{
    TEST_CASE("Plane - NearestIntersection - ray above plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes with normal pointing into positive z.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::Double()));

        // Ray starts above plane, points straight into negative z.
        auto ray = Ray(Point(Random::Double(), Random::Double(), 1 + Random::Double()), Vector(0, 0, -Random::Double()));

        auto result = plane.NearestIntersection(ray);
        REQUIRE(result.has_value());

        // As ray is pointing straight down intersection point will have the same x and y as the ray's origin.
        CHECK_THAT(result.value().Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        CHECK_THAT(result.value().SurfaceNormal(), Equals(plane.Normal()));
    }

    TEST_CASE("Plane - NearestIntersection - ray below plane intersecting orthogonally", "[Plane]")
    {
        // Plane on origin covering x,y axes. Negative z is 'below' the plane.
        auto plane = Plane(Point(Random::Double(), Random::Double(), 0), Vector(0, 0, Random::Double()));
        auto ray = Ray(Point(Random::Double(), Random::Double(), -5 - Random::Double()), Vector(0, 0, Random::Double()));

        auto result = plane.NearestIntersection(ray);
		REQUIRE(result.has_value());
        CHECK_THAT(result.value().Point(), Equals(Point(ray.Origin().X(), ray.Origin().Y(), 0)));
        CHECK_THAT(result.value().SurfaceNormal(), Equals(-plane.Normal()));
    }
}