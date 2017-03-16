#pragma once
#include "Intersection.h"
#include "Object.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Scene
{
	class ObjectIntersection : public Intersection
	{
		const Object* object;

	public:
		ObjectIntersection(const Object* object, const Intersection& intersection);

		const Object* Object() const noexcept { return object; }
	};
}
