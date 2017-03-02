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

        virtual Colour ShadePoint(Scene::Scene& scene, Scene::SceneObject& sceneObject, Geometry::Intersection& intersection) const = 0;
    };
}
