#include "stdafx.h"
#include <Matrix.h>
#include "catch.hpp"
#include "Matchers.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Tests::Geometry::MatrixTests
{
	TEST_CASE("Matrix - Zero", "[Matrix]")
	{
		CHECK(Matrix::Zero().IsZero());
		CHECK(!Matrix::Zero().IsIdentity());
		CHECK(Matrix::Zero() == Matrix::Zero());
		CHECK(Matrix::Zero() != Matrix::Identity());
	}

	TEST_CASE("Matrix - Identity", "[Matrix]")
	{
		CHECK(!Matrix::Identity().IsZero());
		CHECK(Matrix::Identity().IsIdentity());
		CHECK(Matrix::Identity() == Matrix::Identity());
		CHECK(Matrix::Identity() != Matrix::Zero());
	}

	TEST_CASE("Matrix - Scale", "[Matrix]")
	{
		CHECK_THAT(Matrix::Scale(4).Transform(Point(0, 2, -3)), Equals(Point(0, 8, -12)));
		CHECK_THAT(Matrix::Scale(2.5).Transform(Point(2.5, -6, 100)), Equals(Point(6.25, -15, 250)));
		CHECK_THAT(Matrix::Scale(0.5, 1, 3).Transform(Point(5, 7, 3.1)), Equals(Point(2.5, 7, 9.3)));
		CHECK_THAT(Matrix::Scale(1, 0, 0.1).Transform(Point(-5, 3.2, -3)), Equals(Point(-5, 0, -0.3)));
	}
}