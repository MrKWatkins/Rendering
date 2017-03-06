#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Uniform::ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const
    {
        return sceneObject.GetColourAtPoint(intersection.Point());
    }
}
