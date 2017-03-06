#include "stdafx.h"
#include "SceneObject.h"

namespace MrKWatkins::Rendering::Scene
{
    static int nextId;

    SceneObject::SceneObject(std::unique_ptr<Object>&& object, const std::shared_ptr<Materials::Material> material) : id{ nextId++ }, object { move(object) }, material{ material }
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

    Colour SceneObject::GetColourAtPoint(const Point& point) const
    {
        return material->GetColourAtPoint(point);
    }
}
