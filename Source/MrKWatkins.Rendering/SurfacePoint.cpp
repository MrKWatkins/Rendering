#include "stdafx.h"
#include "SurfacePoint.h"

namespace MrKWatkins::Rendering::Shading
{
	SurfacePoint::SurfacePoint(const Rendering::Material & material, const Vector & normal, const Vector & toLight, const Vector & toViewer)
		: material { material }, normal { normal }, toLight { toLight }, toViewer { toViewer }
	{
	}

	double SurfacePoint::ToLightDotNormal() const
	{
		if (!toLightDotNormalCalculated)
		{
			toLightDotNormal = toLight.Dot(normal);
			toLightDotNormalCalculated = true;
		}
		return toLightDotNormal;
	}

	const Vector& SurfacePoint::Reflection() const
	{
		if (!reflectionCalculated)
		{
			// Not using Vector::ReflectAbout as we might have already calculated ToLightDotNormal.
			reflection =  (2 * ToLightDotNormal() * normal - toLight).Normalize();
			reflectionCalculated = true;
		}
		return reflection;
	}
}