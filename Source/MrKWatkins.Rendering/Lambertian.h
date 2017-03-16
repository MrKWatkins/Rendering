#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Lambertian final : public ShadingModel
    {
    public:
        Colour ShadePoint(const Scene::Scene& scene, const Object& sceneObject, const Intersection& intersection) const override;
    };
}
