#include "stdafx.h"
#include "RayTracing.h"
#include "ShadingModel.h"
#include "SurfacePoint.h"
#include "Object.h"

using namespace MrKWatkins::Rendering::Shading;

namespace MrKWatkins::Rendering::Algorithms
{
	RayTracing::RayTracing(std::unique_ptr<ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance) : shadingModel{ move(shadingModel) }, scene{ move(scene) }, camera(0.5, 0.5, -cameraDistance)
	{
	}

    Colour RayTracing::RenderPoint(double x, double y)
    {
        // Create a ray from the (x,y) point at 0 on the z-axis. It should point from the camera
        auto rayOrigin = Point(x, y, 0);
        auto ray = Ray(rayOrigin, rayOrigin - camera);

		return CalculateColour(ray, std::optional<Scene::ObjectIntersection>(), 0);
    }

	Colour RayTracing::CalculateColour(const Ray& ray, const std::optional<Scene::ObjectIntersection> previousIntersection, int recursionDepth)
	{
		auto possibleIntersection = scene->GetClosestIntersection(ray, previousIntersection.has_value() ? previousIntersection.value().Object() : std::optional<const Scene::Object*>());
		if (!possibleIntersection.has_value())
		{
			return scene->GetBackground(ray);
		}

		auto intersection = possibleIntersection.value();

		auto material = intersection.Object()->GetMaterialAtPoint(intersection.Point());
		auto colour = material.Ambient() * scene->AmbientLight();

		auto toViewer = (camera - intersection.Point()).Normalize();

		// Loop over all the lights in the scene to get their contribution.
		for (auto& light : scene->Lights())
		{
			auto intensity = light->GetIntensityAtPoint(intersection.Point());
			if (intensity == 0)
			{
				continue;
			}

			// Check if there is an object in the way of the light.
			// TODO: Try and do this the other way around to avoid having to do the - later on.
			auto lightRay = light->GetRayToPoint(intersection.Point());
			auto closestObjectToLight = scene->GetClosestIntersection(lightRay);
			if (!closestObjectToLight.has_value())
			{
				throw std::logic_error("Light ray does not intersect any object.");
			}
			if (*closestObjectToLight.value().Object() != *intersection.Object())
			{
				continue;
			}

			auto surfacePoint = SurfacePoint(material, intersection.SurfaceNormal(), -lightRay.Direction(), toViewer);

			colour = colour + shadingModel->ShadePoint(surfacePoint) * light->Colour() * intensity;
		}

		// Reflection.
		if (material.Reflectivity() > 0 && recursionDepth < 100)
		{
			auto rayOrigin = intersection.Point();

			auto pointToRay = -ray.Direction();
			auto rayDirection = 2 * pointToRay.Dot(intersection.SurfaceNormal()) * intersection.SurfaceNormal() - pointToRay;
			auto ray = Ray(rayOrigin, rayDirection);

			colour = colour + material.Reflectivity() * CalculateColour(ray, possibleIntersection, recursionDepth + 1);
		}

		return colour;
	}
}
