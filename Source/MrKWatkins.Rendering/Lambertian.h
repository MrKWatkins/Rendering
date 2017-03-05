#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Lambertian : public ShadingModel
    {
    public:
        Colour ShadePoint(const Scene::Scene& scene, const Scene::SceneObject& sceneObject, const Geometry::Intersection& intersection) const override;
    };
}
