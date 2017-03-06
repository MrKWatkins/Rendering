#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Uniform : public ShadingModel
    {
    public:
        Colour ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const override;
    };
}
