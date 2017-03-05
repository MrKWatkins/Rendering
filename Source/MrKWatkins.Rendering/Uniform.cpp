#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Uniform::ShadePoint(const Scene::Scene& scene, const Scene::SceneObject& sceneObject, const Geometry::Intersection& intersection) const
    {
        return sceneObject.Colour();
    }
}
