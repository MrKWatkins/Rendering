#include "stdafx.h"
#include "SceneObject.h"

namespace MrKWatkins::Rendering::Scene
{
    SceneObject::SceneObject(std::unique_ptr<Geometry::Object>&& object, Rendering::Colour colour) : object{ move(object) }, colour{ colour }
    {
    }

    Optional<Geometry::Point> SceneObject::NearestIntersection(const Geometry::Ray& ray) const
    {
        return object->NearestIntersection(ray);
    }
}
