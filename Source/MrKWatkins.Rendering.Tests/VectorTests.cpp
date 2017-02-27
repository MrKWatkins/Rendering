#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"
#include "Matchers.hpp"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::VectorTests
{
    TEST_CASE("Length")
    {
        REQUIRE(Vector(4, -6, 1.2).Length() == Approx(sqrt(16 + 36 + 1.44)));
        REQUIRE(Vector::Zero().Length() == Approx(0));
    }

    TEST_CASE("Addition")
    {
        REQUIRE_THAT(Vector(1, 2.5, -34) + Vector(2, 3.2, 12), Equals(Vector(3, 5.7, -22)));
        REQUIRE_THAT(Vector(7.3, -4, 23) + Vector::Zero(), Equals(Vector(7.3, -4, 23)));
    }

    TEST_CASE("Subtraction")
    {
        REQUIRE_THAT(Vector(6, 7.5, 34) - Vector(2, 3.2, -12), Equals(Vector(4, 4.3, 46)));
        REQUIRE_THAT(Vector(6, 7.5, 34) - Vector::Zero(), Equals(Vector(6, 7.5, 34)));
    }

    TEST_CASE("Multiplication")
    {
        REQUIRE_THAT(Vector(2, 3.1, -4) * 5, Equals(Vector(10, 15.5, -20)));
        REQUIRE_THAT(5 * Vector(2, 3.1, -4), Equals(Vector(10, 15.5, -20)));
        REQUIRE_THAT(Vector(6, 7.5, 34) * 0, Equals(Vector::Zero()));
    }

    TEST_CASE("Division")
    {
        REQUIRE_THAT(Vector(10, 15.5, -20) / 5, Equals(Vector(2, 3.1, -4)));
        REQUIRE_THROWS_AS(Vector(6, 7.5, 34) / 0, std::invalid_argument);
    }
}
