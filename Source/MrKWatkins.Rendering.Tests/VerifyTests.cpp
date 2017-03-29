#include "stdafx.h"
#include <Verify.h>
#include "catch.hpp"

namespace MrKWatkins::Rendering::Tests::VerifyTests
{
	TEST_CASE("Verify - ZeroToOne", "[Verify]")
	{
		CHECK_NOTHROW(Verify::ZeroToOne(0, "param"));
		CHECK_NOTHROW(Verify::ZeroToOne(0.0, "param"));

		CHECK_NOTHROW(Verify::ZeroToOne(0.5, "param"));

		CHECK_NOTHROW(Verify::ZeroToOne(1, "param"));
		CHECK_NOTHROW(Verify::ZeroToOne(1.0, "param"));

		CHECK_THROWS_WITH(Verify::ZeroToOne(-1, "intTooLow"), "Value of intTooLow is -1 which is not in the range 0 -> 1.");
		CHECK_THROWS_WITH(Verify::ZeroToOne(-0.1, "doubleTooLow"), "Value of doubleTooLow is -0.100000 which is not in the range 0 -> 1.");

		CHECK_THROWS_WITH(Verify::ZeroToOne(2, "intTooHigh"), "Value of intTooHigh is 2 which is not in the range 0 -> 1.");
		CHECK_THROWS_WITH(Verify::ZeroToOne(2.1, "doubleTooHigh"), "Value of doubleTooHigh is 2.100000 which is not in the range 0 -> 1.");
	}

	TEST_CASE("Verify - LessThan", "[Verify]")
	{
		CHECK_NOTHROW(Verify::LessThan(5, 2, "param"));
		CHECK_NOTHROW(Verify::LessThan(7.4, 2.5, "param"));

		CHECK_THROWS_WITH(Verify::LessThan(-6, -6, "intEqual"), "Value of intEqual is -6 which is not less than -6.");
		CHECK_THROWS_WITH(Verify::LessThan(-7.0, -7.0, "doubleEqual"), "Value of doubleEqual is -7.000000 which is not less than -7.000000.");

		CHECK_THROWS_WITH(Verify::LessThan(-6, 4, "intGreater"), "Value of intGreater is 4 which is not less than -6.");
		CHECK_THROWS_WITH(Verify::LessThan(2.4, 2.41, "doubleGreater"), "Value of doubleGreater is 2.410000 which is not less than 2.400000.");
	}

	TEST_CASE("Verify - LessThanOrEqualTo", "[Verify]")
	{
		CHECK_NOTHROW(Verify::LessThanOrEqualTo(5, 2, "param"));
		CHECK_NOTHROW(Verify::LessThanOrEqualTo(-3, -3, "param"));

		CHECK_THROWS_WITH(Verify::LessThanOrEqualTo(-6, 4, "intGreater"), "Value of intGreater is 4 which is not less than or equal to -6.");
	}

	TEST_CASE("Verify - GreaterThan", "[Verify]")
	{
		CHECK_NOTHROW(Verify::GreaterThan(1, 2, "param"));
		CHECK_NOTHROW(Verify::GreaterThan(2.4, 7.5, "param"));

		CHECK_THROWS_WITH(Verify::GreaterThan(-6, -6, "intEqual"), "Value of intEqual is -6 which is not greater than -6.");
		CHECK_THROWS_WITH(Verify::GreaterThan(-7.0, -7.0, "doubleEqual"), "Value of doubleEqual is -7.000000 which is not greater than -7.000000.");

		CHECK_THROWS_WITH(Verify::GreaterThan(4, -7, "intGreater"), "Value of intGreater is -7 which is not greater than 4.");
		CHECK_THROWS_WITH(Verify::GreaterThan(2.4, 2.39, "doubleGreater"), "Value of doubleGreater is 2.390000 which is not greater than 2.400000.");
	}

	TEST_CASE("Verify - GreaterThanOrEqualTo", "[Verify]")
	{
		CHECK_NOTHROW(Verify::GreaterThanOrEqualTo(3, 5, "param"));
		CHECK_NOTHROW(Verify::GreaterThanOrEqualTo(-3, -3, "param"));

		CHECK_THROWS_WITH(Verify::GreaterThanOrEqualTo(6, -4, "intGreater"), "Value of intGreater is -4 which is not greater than or equal to 6.");
	}
}