#include "stdafx.h"
#include "Object.h"
#include "ObjectIntersection.h"

namespace MrKWatkins::Rendering::Scene
{
	ObjectIntersection::ObjectIntersection(const SurfaceIntersection& surfaceIntersection, const Scene::Object* object) : SurfaceIntersection(surfaceIntersection), object { object }
	{
	}
}