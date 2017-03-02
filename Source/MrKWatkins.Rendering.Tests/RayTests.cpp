#include "stdafx.h"
#include "catch.hpp"
#include "Matchers.hpp"
#include "Random.h"
#include "../MrKWatkins.Rendering/Ray.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::RayTests
{
    TEST_CASE("Ray - Construction normalizes direction vector", "[Ray]")
    {
        CHECK_THAT(Ray(Point(1, 2, 3), Vector(5, 0, 0)).Direction(), Equals(Vector(1, 0, 0)));
    }
}