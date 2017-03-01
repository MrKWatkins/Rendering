#include "stdafx.h"
#include "Ray.h"

namespace MrKWatkins::Rendering::Geometry
{
    Ray::Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction.Normalize())
    {
    }
}
