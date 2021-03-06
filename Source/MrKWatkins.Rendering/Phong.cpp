#include "stdafx.h"
#include "Phong.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour Phong::ShadePoint(const SurfacePoint & surfacePoint) const
	{
		auto material = surfacePoint.Material();
		auto phong = surfacePoint.ToLightDotNormal() * material.Diffuse();	// Diffuse contribution.

		// Specular contribution.
		if (!material.Specular().IsBlack() && surfacePoint.ToLightDotNormal() > 0)
		{
			auto rDotV = surfacePoint.Reflection().Dot(surfacePoint.ToViewer());
			phong = phong + material.Specular() * pow(std::max(0.0, rDotV), material.Shininess());
		}

		return phong;
	}
}
