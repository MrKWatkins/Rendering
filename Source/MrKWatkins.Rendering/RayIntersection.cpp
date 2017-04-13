#include "stdafx.h"
#include "RayIntersection.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	RayIntersection::RayIntersection(double d, bool intersectingOutside, double u, double v, const Solid* childSolid) : d{ d }, intersectingOutside{ intersectingOutside }, u{ u }, v{ v }, childSolid{ childSolid }
	{
		VERIFY_NOT_NEGATIVE(d);
		VERIFY_ZERO_TO_ONE(u);
		VERIFY_ZERO_TO_ONE(v);
		VERIFY_ZERO_TO_ONE(u + v);
	}

	RayIntersection::RayIntersection(double d, bool intersectingOutside) : RayIntersection(d, intersectingOutside, 0.0, 0.0, nullptr)
	{
	}

	RayIntersection::RayIntersection(double d, bool intersectingOutside, double u, double v) : RayIntersection(d, intersectingOutside, u, v, nullptr)
	{
	}

	RayIntersection::RayIntersection(const RayIntersection& childIntersection, const Solid* childSolid) : RayIntersection(childIntersection.d, childIntersection.intersectingOutside, childIntersection.u, childIntersection.v, childSolid)
	{
	}
}
