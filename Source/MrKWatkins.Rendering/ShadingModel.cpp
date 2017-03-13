#include "stdafx.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
	bool ShadingModel::IsRayToPointOnObjectBlocked(const Scene::Scene& scene, const Ray& ray, const SceneObject& sceneObject, const Point& pointOnObject) const
	{
		auto distanceToPoint = ray.Origin().DistanceFrom(pointOnObject);
		for (auto&& otherObject : scene.Objects())
		{
			if (*otherObject == sceneObject)
			{
				continue;
			}

			auto objectIntersection = otherObject->NearestIntersection(ray);
			if (!objectIntersection.HasIntersection())
			{
				continue;
			}

			auto distanceToObject = ray.Origin().DistanceFrom(objectIntersection.Point());
			if (distanceToObject < distanceToPoint)
			{
				return true;
			}
		}

		return false;
	}
}