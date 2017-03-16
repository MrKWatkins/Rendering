#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
	Colour Uniform::ShadePoint(const SurfacePoint& surfacePoint) const
    {
        return surfacePoint.Material().Ambient();
    }
}
