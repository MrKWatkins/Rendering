#include "stdafx.h"
#include "catch.hpp"
#include "Matchers.hpp"
#include "Random.h"
#include "../MrKWatkins.Rendering/Point.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::PointTests
{
    auto a = Random::Point();
    auto b = Random::Point();
    auto c = Random::Point();
    auto r = Random::Double();
    auto s = Random::Double();

    TEST_CASE("Point - Addition", "[Point]")
    {
        CHECK_THAT(Point(1, 2.5, -34) + Vector(2, 3.2, 12), Equals(Point(3, 5.7, -22)));

        auto point = Random::Point();
        CHECK_THAT(point + Vector::Zero(), Equals(point));

        auto vector = Random::Vector();
        CHECK_THAT(Point::Origin() + vector, Equals(Point(vector.X(), vector.Y(), vector.Z())));
    }

    TEST_CASE("Point - Subtraction", "[Point]")
    {
        CHECK_THAT(Point(6, 7.5, 34) - Point(2, 3.2, -12), VectorEquals(Vector(4, 4.3, 46)));

        auto point = Random::Point();
        CHECK_THAT(point - Point::Origin(), VectorEquals(Vector(point)));
        CHECK_THAT(Point::Origin() - point , VectorEquals(-Vector(point)));
    }

    TEST_CASE("Point - DistanceFrom", "[Point]")
    {
        CHECK(Point(12, 1, 1.7).DistanceFrom(Point(8, 7, 0.5)) == Approx(sqrt(16 + 36 + 1.44)));

        auto a = Random::Point();
        CHECK(a.DistanceFrom(Point::Origin()) == Approx(Vector(a).Length()));

        auto b = Random::Point();
        CHECK(a.DistanceFrom(b) == Approx(b.DistanceFrom(a)));
    }
}
