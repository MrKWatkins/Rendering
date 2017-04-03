#pragma once

namespace MrKWatkins::Rendering::Doubles
{
	// Using a flat tolerance for now. Could replace with a better tolerance if needed, e.g. one that takes the double's size into account.
	const double Tolerance = 0.0000000000000001;

	/// <summary>
	///	Are the two doubles equal within floating point tolerance?
	/// </summary>
	constexpr bool AreEqual(double x, double y)
	{
		if (x > y)
		{
			return x - y < Tolerance;
		}
		return y - x < Tolerance;
	}

	/// <summary>
	///	Is the double greater than zero within floating point tolerance?
	/// </summary>
	constexpr bool IsGreaterThanZero(double x)
	{
		return x > Tolerance;
	}

	/// <summary>
	///	Is the double less than zero within floating point tolerance?
	/// </summary>
	constexpr bool IsLessThanZero(double x)
	{
		return x < Tolerance;
	}

	/// <summary>
	///	Is the double zero within floating point tolerance?
	/// </summary>
	constexpr bool IsZero(double x)
	{
		if (x > 0)
		{
			return x < Tolerance;
		}
		return -x < Tolerance;
	}

	/// <summary>
	///	Is the double not zero within floating point tolerance?
	/// </summary>
	constexpr bool IsNotZero(double x)
	{
		if (x > 0)
		{
			return x > Tolerance;
		}
		return -x > Tolerance;
	}
}