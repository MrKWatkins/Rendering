#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Uniform final : public ShadingModel
    {
    public:
		Colour ShadePoint(const SurfacePoint& surfacePoint) const override;
    };
}
