#pragma once
#include "Object.h"
#include <memory>
#include "Colour.h"
#include "Intersection.h"

namespace MrKWatkins::Rendering::Scene
{
    class SceneObject
    {
        int id;
        std::unique_ptr<Geometry::Object> object;
        Colour colour;

    public:
        SceneObject(std::unique_ptr<Geometry::Object>&& object, Colour colour);
        SceneObject(const SceneObject& toCopy) = delete;
        ~SceneObject() = default;

        bool operator==(const SceneObject& other) const;
        bool operator!=(const SceneObject& other) const;

        Geometry::Intersection NearestIntersection(const Geometry::Ray& ray) const;
        Colour Colour() const noexcept { return colour; }
    };
}
