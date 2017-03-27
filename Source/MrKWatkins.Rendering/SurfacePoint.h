#pragma once
#include "Vector.h"
#include "Material.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Shading
{
	class SurfacePoint final
	{
		Material material;
		Vector normal;
		Vector toLight;
		Vector toViewer;

		mutable bool toLightDotNormalCalculated = false;
		mutable double toLightDotNormal = 0.0;

		mutable bool reflectionCalculated = false;
		mutable Vector reflection{ 0, 0, 0 };

	public:
		SurfacePoint(const Material& material, const Vector& normal, const Vector& toLight, const Vector& toViewer);

		const Material& Material() const noexcept { return material; }
		const Vector& Normal() const noexcept { return normal; }
		const Vector& ToLight() const noexcept { return toLight; }
		const Vector& ToViewer() const noexcept { return toViewer; }

		double ToLightDotNormal() const;
		const Vector& Reflection() const;
	};
}
