#include "stdafx.h"
#include <algorithm>
#include "Phong.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour Phong::ShadePoint(const Scene::Scene& scene, const Object& sceneObject, const Intersection& intersection) const
	{
		auto material = sceneObject.GetMaterialAtPoint(intersection.Point());
		auto colour = material.Ambient() * scene.AmbientLight();

		auto v = -Vector::K();
		auto n = intersection.SurfaceNormal();

		// Loop over all the lights in the scene to get their contribution.
		for (auto&& light : scene.Lights())
		{
			auto intensity = light->GetIntensityAtPoint(intersection.Point());
			if (intensity == 0)
			{
				continue;
			}

			// Check if there is an object in the way of the light.
			auto lightRay = light->GetRayToPoint(intersection.Point());
			auto closestObjectToLight = scene.GetClosestIntersection(lightRay);
			if (*closestObjectToLight.value().Object() != sceneObject)	// No need to check has_value - we must intersect.
			{
				continue;
			}

			auto l = -lightRay.Direction();
			auto lDotN = l.Dot(n);
			auto phong = colour + material.Diffuse() * lDotN;	// Diffuse contribution.

			if (!material.Specular().IsBlack() && lDotN > 0)
			{
				auto r = (2 * lDotN * n - l).Normalize();

				phong = phong + material.Specular() * pow(std::max(0.0, r.Dot(v)), material.Shininess());
			}

			colour = colour + phong * light->Colour() * intensity;
		}

		return colour;
	}
}
