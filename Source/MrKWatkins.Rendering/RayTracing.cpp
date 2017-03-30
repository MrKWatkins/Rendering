#include "stdafx.h"
#include "RayTracing.h"
#include "ShadingModel.h"
#include "SurfacePoint.h"
#include "Object.h"

using namespace MrKWatkins::Rendering::Shading;

namespace MrKWatkins::Rendering::Algorithms
{
	RayTracing::RayTracing(std::unique_ptr<ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance, int maximumRecursionDepth) 
		: shadingModel{ move(shadingModel) }, scene{ move(scene) }, maximumRecursionDepth{ maximumRecursionDepth }, camera{ 0.5, 0.5, -cameraDistance }
	{
	}

    Colour RayTracing::RenderPoint(double x, double y) const
    {
        // Create a ray from the (x,y) point at 0 on the z-axis. It should point from the camera
        auto rayOrigin = Point(x, y, 0);
        auto ray = Ray(rayOrigin, rayOrigin - camera);

		return CalculateColour(ray, std::optional<Scene::ObjectIntersection>(), 0);
    }

	Colour RayTracing::CalculateColour(const Ray& ray, const std::optional<Scene::ObjectIntersection> previousIntersection, int recursionDepth) const
	{
		// Ignore the previous object when calculating the nearest intersection in case it turns up. This will break when we have more complicated objects!
		auto possibleIntersection = scene->GetClosestIntersection(ray, previousIntersection.has_value() ? previousIntersection.value().Object() : std::optional<const Scene::Object*>());
		if (!possibleIntersection.has_value())
		{
			return scene->GetBackground(ray);
		}

		auto intersection = possibleIntersection.value();
		auto material = intersection.Object()->GetMaterialAtPoint(intersection.Point());

		// If we're at the recursion depth then only include direct light.
		if (recursionDepth == maximumRecursionDepth)
		{
			return CalculateDirectLight(material, intersection);
		}

		auto colour = Colour::Black();
		colour = colour + (1.0 - material.Reflectivity() - material.Transmittance()) * CalculateDirectLight(material, intersection);
		colour = colour + CalculateReflection(ray, material, intersection, recursionDepth);
		colour = colour + CalculateTransmittance(ray, material, intersection, recursionDepth);
		return colour;
	}

	Colour RayTracing::CalculateDirectLight(const Material& material, const Scene::ObjectIntersection intersection) const
	{
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

		return colour;
	}

	Colour RayTracing::CalculateReflection(const Ray& ray, const Material& material, const Scene::ObjectIntersection intersection, int recursionDepth) const
	{
		if (material.Reflectivity() == 0)
		{
			return Colour::Black();
		}

		auto surfaceToRayOrigin = -ray.Direction();
		auto reflectionOrigin = intersection.Point();
		auto reflectionDirection = 2 * surfaceToRayOrigin.Dot(intersection.SurfaceNormal()) * intersection.SurfaceNormal() - surfaceToRayOrigin;

		auto reflection = Ray(reflectionOrigin, reflectionDirection);
		return material.Reflectivity() * CalculateColour(reflection, intersection, recursionDepth + 1);
	}

	Ray CalculateExitRayForTransmittance(const Ray& ray, const Material& material, const Scene::ObjectIntersection intersection)
	{
		// TODO: Take refractive index into account rather than just using ray.Direction().
		auto rayPassingThroughObject = Ray(intersection.Point(), ray.Direction());

		// This assumes there are no objects inside the object! TODO: Allow overlapping objects.
		auto exitPoint = intersection.Object()->NearestIntersection(rayPassingThroughObject);
		if (!exitPoint.has_value())
		{
			// Must've been a 2D object.
			return rayPassingThroughObject;
		}

		// TODO: Take refractive index into account rather than just using ray.Direction().
		return Ray(exitPoint.value().Point(), ray.Direction());
	}

	Colour RayTracing::CalculateTransmittance(const Ray& ray, const Material& material, const Scene::ObjectIntersection intersection, int recursionDepth) const
	{
		if (material.Transmittance() == 0)
		{
			return Colour::Black();
		}

		auto exitRay = CalculateExitRayForTransmittance(ray, material, intersection);

		return material.Transmittance() * CalculateColour(exitRay, intersection, recursionDepth + 1);
	}
}
