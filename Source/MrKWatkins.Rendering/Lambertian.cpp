#include "stdafx.h"
#include "Lambertian.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour Lambertian::ShadePoint(const SurfacePoint & surfacePoint) const
	{
		// Lambertian reflectance is:
		// C = L.N Cs Cl I
		// Where:
		//  C  = Final colour.
		//  L  = Normal vector from surface to light.
		//  N  = Surface normal.
		//  Cs = Colour of surface at the point.
		//  Cl = Colour of light.
		//  I  = Intensity of light at the point.

		if (surfacePoint.Material().Shininess() >  0.5 * 128)
		{
			auto ldb = surfacePoint.ToLightDotNormal();
		}

		return surfacePoint.ToLightDotNormal() * surfacePoint.Material().Diffuse();
	}
}
