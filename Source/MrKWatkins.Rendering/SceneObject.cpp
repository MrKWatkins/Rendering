#include "stdafx.h"
#include "SceneObject.h"

namespace MrKWatkins::Rendering::Scene
{
    static int nextId;

    SceneObject::SceneObject(std::unique_ptr<Geometry::Object>&& object, Rendering::Colour colour) : id{ nextId++ }, object { move(object) }, colour{ colour }
    {
    }

    bool SceneObject::operator==(const SceneObject& other) const
    {
        return id == other.id;
    }

    bool SceneObject::operator!=(const SceneObject& other) const
    {
        return id != other.id;
    }

    Geometry::Intersection SceneObject::NearestIntersection(const Geometry::Ray& ray) const
    {
        return object->NearestIntersection(ray);
    }
}
