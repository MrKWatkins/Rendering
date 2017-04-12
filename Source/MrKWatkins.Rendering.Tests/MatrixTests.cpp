#include "stdafx.h"
#include <Matrix.h>
#include "catch.hpp"

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
}