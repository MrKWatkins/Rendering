#include "stdafx.h"
#include <algorithm>
#include "Phong.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour Phong::ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const
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

			auto lightRay = light->GetLightRayToPoint(intersection.Point());
			if (IsRayToPointOnObjectBlocked(scene, lightRay, sceneObject, intersection.Point()))
			{
				continue;
			}

			auto l = -lightRay.Direction();
			auto phong = colour + material.Diffuse() * l.Dot(n);	// Diffuse contribution.

			auto shininess = material.Shininess();
			if (shininess > 0 && l.Dot(n) > 0)
			{
				auto r = (2 * l.Dot(n) * n - l).Normalize();

				phong = phong + material.Specular() * pow(std::max(0.0, r.Dot(v)), shininess);
			}

			colour = colour + phong * light->Colour() * intensity;
		}

		return colour;
	}
}
