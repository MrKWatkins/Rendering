#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"
#include "Matchers.hpp"
#include <random>

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::VectorTests
{
    std::default_random_engine generator{ std::random_device{}() };
    std::uniform_real_distribution<double> distribution{ 0, 100 };

    Vector RandomVector()
    {
        return Vector(distribution(generator), distribution(generator), distribution(generator));
    }

    auto a = RandomVector();
    auto b = RandomVector();
    auto c = RandomVector();
    auto r = distribution(generator);
    auto s = distribution(generator);

    TEST_CASE("Length")
    {
        CHECK(Vector(4, -6, 1.2).Length() == Approx(sqrt(16 + 36 + 1.44)));
        CHECK(Vector::Zero().Length() == Approx(0));
    }

    TEST_CASE("Addition")
    {
        CHECK_THAT(Vector(1, 2.5, -34) + Vector(2, 3.2, 12), Equals(Vector(3, 5.7, -22)));

        auto vector = RandomVector();
        CHECK_THAT(vector + Vector::Zero(), Equals(vector));
    }

    TEST_CASE("Subtraction")
    {
        CHECK_THAT(Vector(6, 7.5, 34) - Vector(2, 3.2, -12), Equals(Vector(4, 4.3, 46)));

        auto vector = RandomVector();
        CHECK_THAT(vector - Vector::Zero(), Equals(vector));
    }

    TEST_CASE("Multiplication")
    {
        CHECK_THAT(Vector(2, 3.1, -4) * 5, Equals(Vector(10, 15.5, -20)));
        CHECK_THAT(5 * Vector(2, 3.1, -4), Equals(Vector(10, 15.5, -20)));
        CHECK_THAT(RandomVector() * 0, Equals(Vector::Zero()));
    }

    TEST_CASE("Division")
    {
        CHECK_THAT(Vector(10, 15.5, -20) / 5, Equals(Vector(2, 3.1, -4)));
        CHECK_THROWS_AS(RandomVector() / 0, std::invalid_argument);
    }

    TEST_CASE("Dot Product")
    {
        CHECK(Vector(1, 2, 3).Dot(Vector(4, -5, 6)) == 12);
        CHECK(Vector(4, -5, 6).Dot(Vector(1, 2, 3)) == 12);

        CHECK(RandomVector().Dot(Vector::Zero()) == 0);

        // Commutative:
        CHECK(a.Dot(b) == Approx(b.Dot(a)));

        // Distributive:
        CHECK(a.Dot(b + c) == Approx(a.Dot(b) + a.Dot(c)));

        // Bilinear:
        CHECK(a.Dot(r*b + c) == Approx(r*a.Dot(b) + a.Dot(c)));

        // Scalar multiplication:
        CHECK((r * a).Dot(s * b) == Approx(r*s*(a.Dot(b))));
    }

    TEST_CASE("Cross Product")
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
