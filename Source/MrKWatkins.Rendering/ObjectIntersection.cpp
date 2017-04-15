#include "stdafx.h"
#include "Object.h"
#include "ObjectIntersection.h"

namespace MrKWatkins::Rendering::Scene
{
	ObjectIntersection::ObjectIntersection(const Scene::Object* object, std::unique_ptr<Geometry::Intersection>&& intersection)
		: object { object }, intersection { move(intersection) }
	{
	}
}
