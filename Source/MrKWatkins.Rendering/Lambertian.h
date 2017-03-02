#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Lambertian : public ShadingModel
    {
    public:
        Colour ShadePoint(Scene::Scene& scene, Scene::SceneObject& sceneObject, Geometry::Intersection& intersection) const override;
    };
}
