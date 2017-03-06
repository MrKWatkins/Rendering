#include "stdafx.h"
#include "SceneObject.h"

namespace MrKWatkins::Rendering::Scene
{
    static int nextId;

    SceneObject::SceneObject(std::unique_ptr<Object>&& object, const Rendering::Colour& colour) : id{ nextId++ }, object { move(object) }, colour{ colour }
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

    Intersection SceneObject::NearestIntersection(const Ray& ray) const
    {
        return object->NearestIntersection(ray);
    }
}
