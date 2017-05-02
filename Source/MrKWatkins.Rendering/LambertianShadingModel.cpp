#include "stdafx.h"
#include "LambertianShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour LambertianShadingModel::ShadePoint(const SurfacePoint & surfacePoint) const
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

		// Cl and I are performed in RayTracing::CalculateDirectLight so we just need to return L.N Cs here.
		return surfacePoint.ToLightDotNormal() * surfacePoint.Material().Diffuse();
	}
}
