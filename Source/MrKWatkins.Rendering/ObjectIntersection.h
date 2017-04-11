#pragma once
#include "Object.h"
#include "SurfaceIntersection.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Scene
{
	class ObjectIntersection : public SurfaceIntersection
	{
		const Object* object;

	public:
		ObjectIntersection(const SurfaceIntersection& surfaceIntersection, const Object* object);

		const Object* Object() const noexcept { return object; }
	};
}
