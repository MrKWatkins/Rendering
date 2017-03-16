#include "stdafx.h"
#include "Object.h"
#include "ObjectIntersection.h"

namespace MrKWatkins::Rendering::Scene
{
	ObjectIntersection::ObjectIntersection(const Scene::Object* object, const Intersection & intersection) : Intersection(intersection), object { object }
	{
	}
}