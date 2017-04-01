#pragma once
#include "Vector.h"
#include "Point.h"
#include "AxisAlignedBox.h"

namespace MrKWatkins::Rendering::Tests::Random
{
	/// <summary>
	/// Returns a double in the range -1000 -> 1000.
	/// </summary>
	double Double();

	/// <summary>
	/// Returns a double in the specified range.
	/// </summary>
	double Range(double minimum, double maximum);

	/// <summary>
	/// Returns a double in the range 0 -> 1000.
	/// </summary>
	double Positive();

	/// <summary>
	/// Returns a double in the range 0.001 -> 1000.
	/// </summary>
	double GreaterThanZero();

	/// <summary>
	/// Returns a double in the range -1000 -> 0.
	/// </summary>
	double Negative();

	/// <summary>
	/// Returns a double in the range -1000 -> -0.001.
	/// </summary>
	double LessThanZero();

	/// <summary>
	/// Returns a double in the range 0 -> 1.
	/// </summary>
	double ZeroToOne();

	/// <summary>
	/// Returns a Vector with components in the range -1000 -> 1000.
	/// </summary>
	Geometry::Vector Vector();

	/// <summary>
	/// Returns a Point with components in the range -1000 -> 1000.
	/// </summary>
	Geometry::Point Point();

	/// <summary>
	/// Returns a Point at a random position inside the specified AxisAlignedBox.
	/// </summary>
	Geometry::Point PointInside(const Geometry::AxisAlignedBox& box);
}
