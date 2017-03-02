#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Uniform : public ShadingModel
    {
    public:
        Colour ShadePoint(Scene::Scene& scene, Geometry::Point point, Colour colourOfPoint, Geometry::Vector surfaceNormal) const override;
    };
}
