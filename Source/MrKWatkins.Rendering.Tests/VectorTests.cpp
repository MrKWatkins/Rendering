#include "stdafx.h"
#include <Vector.h>
#include "catch.hpp"
#include "Matchers.h"
#include "Random.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::VectorTests
{
    auto a = Random::Vector();
    auto b = Random::Vector();
    auto c = Random::Vector();
    auto r = Random::Double();
    auto s = Random::Double();

    TEST_CASE("Vector - Length", "[Vector]")
    {
        CHECK(Vector(4, -6, 1.2).Length() == Approx(sqrt(16 + 36 + 1.44)));
        CHECK(Vector::Zero().Length() == Approx(0));
    }

    TEST_CASE("Vector - Addition", "[Vector]")
    {
        CHECK_THAT(Vector(1, 2.5, -34) + Vector(2, 3.2, 12), Equals(Vector(3, 5.7, -22)));

        auto vector = Random::Vector();
        CHECK_THAT(vector + Vector::Zero(), Equals(vector));
    }

    TEST_CASE("Vector - Subtraction", "[Vector]")
    {
        CHECK_THAT(Vector(6, 7.5, 34) - Vector(2, 3.2, -12), Equals(Vector(4, 4.3, 46)));

        auto vector = Random::Vector();
        CHECK_THAT(vector - Vector::Zero(), Equals(vector));
    }

    TEST_CASE("Vector - Multiplication", "[Vector]")
    {
        CHECK_THAT(Vector(2, 3.1, -4) * 5, Equals(Vector(10, 15.5, -20)));
        CHECK_THAT(5 * Vector(2, 3.1, -4), Equals(Vector(10, 15.5, -20)));
        CHECK_THAT(Random::Vector() * 0, Equals(Vector::Zero()));
    }

    TEST_CASE("Vector - Division", "[Vector]")
    {
        CHECK_THAT(Vector(10, 15.5, -20) / 5, Equals(Vector(2, 3.1, -4)));
        CHECK_THROWS_AS(Random::Vector() / 0, std::invalid_argument);
    }

    TEST_CASE("Vector - Dot Product", "[Vector]")
    {
        CHECK(Vector(1, 2, 3).Dot(Vector(4, -5, 6)) == 12);
        CHECK(Vector(4, -5, 6).Dot(Vector(1, 2, 3)) == 12);

        CHECK(Random::Vector().Dot(Vector::Zero()) == 0);

        // Commutative:
        CHECK(a.Dot(b) == Approx(b.Dot(a)));

        // Distributive:
        CHECK(a.Dot(b + c) == Approx(a.Dot(b) + a.Dot(c)));

        // Bilinear:
        CHECK(a.Dot(r*b + c) == Approx(r*a.Dot(b) + a.Dot(c)));

        // Scalar multiplication:
        CHECK((r * a).Dot(s * b) == Approx(r*s*(a.Dot(b))));
    }

    TEST_CASE("Vector - Cross Product", "[Vector]")
    {
        CHECK_THAT(Vector(3, -3, 1).Cross(Vector(4, 9, 2)), Equals(Vector(-15, -2, 39)));

        // Anti-commutative:
        CHECK_THAT(a.Cross(b), Equals(-(b.Cross(a))));

        // Distributive:
        CHECK_THAT(a.Cross(b + c), Equals(a.Cross(b) + a.Cross(c)));

        // Scalar multiplication:
        CHECK_THAT((r*a).Cross(b), Equals(a.Cross(r*b)));
        CHECK_THAT((r*a).Cross(b), Equals(r*(a.Cross(b))));

        // Jacobi identity:
        CHECK_THAT(a.Cross(b.Cross(c)) + b.Cross(c.Cross(a)) + c.Cross(a.Cross(b)), Equals(Vector::Zero()));
    }
}
