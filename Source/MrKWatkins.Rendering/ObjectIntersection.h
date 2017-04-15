#pragma once
#include "Object.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Scene
{
	class ObjectIntersection final
	{
		const Object* object;
		const std::unique_ptr<Intersection> intersection;
	public:
		ObjectIntersection(const Object* object, std::unique_ptr<Intersection>&& intersection);

		const Object* Object() const noexcept { return object; }
		const Intersection* Intersection() const noexcept { return intersection.get(); }
		const Point& Point() const noexcept { return intersection->Point(); }
		const Vector& Normal() const noexcept { return intersection->Normal(); }
	};
}
