#pragma once
#include "Colour.h"
#include "Intersection.h"
#include "Scene.h"

namespace MrKWatkins::Rendering::Shading
{
    class ShadingModel
    {
    public:
        virtual ~ShadingModel() = default;

        virtual Colour ShadePoint(Scene::Scene& scene, Geometry::Point point, Colour colourOfPoint, Geometry::Vector surfaceNormal) const = 0;
    };
}
