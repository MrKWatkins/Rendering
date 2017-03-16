#include "stdafx.h"
#include "Uniform.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Uniform::ShadePoint(const Scene::Scene& scene, const Object& object, const Intersection& intersection) const
    {
        return object.GetMaterialAtPoint(intersection.Point()).Ambient();
    }
}
