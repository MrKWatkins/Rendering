#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Uniform::ShadePoint(Scene::Scene& scene, Scene::SceneObject& sceneObject, Geometry::Intersection& intersection) const
    {
        return sceneObject.Colour();
    }
}
