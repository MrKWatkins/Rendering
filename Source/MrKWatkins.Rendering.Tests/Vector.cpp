#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"

namespace MrKWatkins::Rendering::Tests::Point
{
    TEST_CASE("Addition")
    {
        auto v0 = Geometry::Vector(1, 2.5, -34);
        auto v1 = Geometry::Vector(2, 3.2, 12);

        auto sum = v0 + v1;
        REQUIRE(sum.X() == 3);
        REQUIRE(sum.Y() == 5.7);
        REQUIRE(sum.Z() == -22);
    }
}
