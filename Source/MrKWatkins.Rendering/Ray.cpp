#include "stdafx.h"
#include "Ray.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
    Ray::Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction.Normalize())
    {
    }

	Point Ray::ResolveDistance(double distance) const
	{
		VERIFY_NOT_NEGATIVE(distance);

		return origin + distance * direction;
	}
}
