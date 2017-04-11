#include "stdafx.h"
#include "RayIntersection.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	RayIntersection::RayIntersection(double d, bool intersectingOutside, const Solid* childSolid) : d{ d }, intersectingOutside{ intersectingOutside }, childSolid{ childSolid }
	{
		VERIFY_NOT_NEGATIVE(d);
	}

	RayIntersection::RayIntersection(double d, bool intersectingOutside) : RayIntersection(d, intersectingOutside, nullptr)
	{
	}

	RayIntersection::RayIntersection(const RayIntersection& childIntersection, const Solid* childSolid) : RayIntersection(childIntersection.d, childIntersection.intersectingOutside, childSolid)
	{
	}
}
