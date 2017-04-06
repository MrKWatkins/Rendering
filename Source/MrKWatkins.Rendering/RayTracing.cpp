#include "stdafx.h"
#include "Doubles.h"
#include "RayTracing.h"
#include "ShadingModel.h"
#include "SurfacePoint.h"
#include "Object.h"

using namespace MrKWatkins::Rendering::Shading;

// TODO: Add debug tracing that can be turned on/off for a given point.
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

		auto reflectivity = material.Reflectivity();
		auto transmittance = CalculateTransmittance(ray, material, intersection, recursionDepth);
		if (transmittance.has_value())
		{
			colour = colour + transmittance.value();
		}
		else
		{
			// Total internal reflection on the exterior. Add the amount of transmittance to reflectivity instead.
			reflectivity += material.Transmittance();
		}
		colour = colour + CalculateReflection(ray, reflectivity, intersection, recursionDepth);
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

	Colour RayTracing::CalculateReflection(const Ray& ray, double reflectivity, const Scene::ObjectIntersection intersection, int recursionDepth) const
	{
		if (Doubles::IsZero(reflectivity))
		{
			return Colour::Black();
		}

		auto surfaceToRayOrigin = -ray.Direction();
		auto reflectionOrigin = intersection.Point();
		auto reflectionDirection = Vector::ReflectAboutNormal(surfaceToRayOrigin, intersection.SurfaceNormal());

		auto reflection = Ray(reflectionOrigin, reflectionDirection);
		return reflectivity * CalculateColour(reflection, intersection, recursionDepth + 1);
	}

	std::optional<Vector> CalculateRefractedDirection(const double sourceRefractiveIndex, const double targetRefractiveIndex, const Vector& rayDirection, const Vector& surfaceNormal)
	{
		// Refracted direction = rs(d - n(d.n))/rt - n sqrt(1 - (rs^2(1-(d.n)^2)/rt^2))
		// Where:
		//	rs = Refractive index of source material, i.e. the material the ray is currently inside.
		//  rt = Refractive index of target material, i.e. the material the ray is passing into.
		//  d  = Direction of ray.
		//  n  = Surface normal.
		auto dDotN = rayDirection.Dot(surfaceNormal);
		auto toBeRooted = 1 - sourceRefractiveIndex * sourceRefractiveIndex * (1 - dDotN * dDotN) / (targetRefractiveIndex * targetRefractiveIndex);
		if (toBeRooted < 0)
		{
			// Total internal reflection.
			return std::optional<Vector>();
		}
		return sourceRefractiveIndex * (rayDirection - surfaceNormal * dDotN) / targetRefractiveIndex - surfaceNormal * sqrt(toBeRooted);
	}

	std::optional<Ray> RayTracing::CalculateExitRayForTransmittance(const Ray& refractedRay, const Material& material, const Scene::Object* object, int* recursionDepth) const
	{
		// This assumes there are no objects inside the object! TODO: Allow overlapping objects.
		auto exitPoint = object->NearestIntersection(refractedRay);
		if (!exitPoint.has_value())
		{
			// Must've been a 2D object.
			return refractedRay;
		}

		auto internalRay = refractedRay;
		auto exitDirection = CalculateRefractedDirection(material.RefractiveIndex(), 1, internalRay.Direction(), exitPoint->SurfaceNormal());
		// If there is no value then we have total internal reflection.
		while (!exitDirection.has_value())
		{
			if (*recursionDepth == maximumRecursionDepth)
			{
				return std::optional<Ray>();
			}
			*recursionDepth = *recursionDepth + 1;	// Being 100% sure I'm not incrementing the pointer here...

			auto internalReflectionDirection = Vector::ReflectAboutNormal(-internalRay.Direction(), exitPoint->SurfaceNormal());
			internalRay = Ray(exitPoint->Point(), internalReflectionDirection);
			exitPoint = object->NearestIntersection(internalRay);
			exitDirection = CalculateRefractedDirection(material.RefractiveIndex(), 1, internalRay.Direction(), exitPoint->SurfaceNormal());
		}

		return Ray(exitPoint->Point(), exitDirection.value());
	}

	std::optional<Colour> RayTracing::CalculateTransmittance(const Ray& ray, const Material& material, const Scene::ObjectIntersection intersection, int recursionDepth) const
	{
		if (Doubles::IsZero(material.Transmittance()))
		{
			return Colour::Black();
		}

		// Work out the direction of refraction.
		auto refractedDirection = CalculateRefractedDirection(1, material.RefractiveIndex(), ray.Direction(), intersection.SurfaceNormal());
		if (!refractedDirection.has_value())
		{
			// Total internal reflection on the exterior. Return no Colour to indicate to that we should use the amount of transmittance for reflection instead.
			return std::optional<Colour>();
		}

		auto refractedRay = Ray(intersection.Point(), refractedDirection.value());
		auto exitRay = CalculateExitRayForTransmittance(refractedRay, material, intersection.Object(), &recursionDepth);
		if (!exitRay.has_value())
		{
			// No exit ray - must be bouncing around inside.
			return Colour::Black();
		}

		return material.Transmittance() * CalculateColour(exitRay.value(), intersection, recursionDepth + 1);
	}
}
