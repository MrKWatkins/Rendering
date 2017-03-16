#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
    class Uniform final : public ShadingModel
    {
    public:
        Colour ShadePoint(const Scene::Scene& scene, const Object& object, const Intersection& intersection) const override;
    };
}
