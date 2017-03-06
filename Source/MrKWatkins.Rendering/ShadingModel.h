#pragma once
#include "Colour.h"
#include "Intersection.h"
#include "Scene.h"

using namespace MrKWatkins::Rendering::Scene;

namespace MrKWatkins::Rendering::Shading
{
    class ShadingModel
    {
    public:
        virtual ~ShadingModel() = default;

        virtual Colour ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const = 0;
    };
}
