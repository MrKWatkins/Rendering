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

        virtual Colour ShadePoint(const Scene::Scene& scene, const Scene::SceneObject& sceneObject, const Geometry::Intersection& intersection) const = 0;
    };
}
