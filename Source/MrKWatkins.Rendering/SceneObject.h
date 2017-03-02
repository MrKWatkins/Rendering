#pragma once
#include "Object.h"
#include <memory>
#include "Colour.h"

namespace MrKWatkins::Rendering::Scene
{
    class SceneObject
    {
        std::unique_ptr<Geometry::Object> object;
        Colour colour;

    public:
        SceneObject(std::unique_ptr<Geometry::Object>&& object, Colour colour);
        SceneObject(const SceneObject& toCopy) = delete;
        ~SceneObject() = default;

        Optional<Geometry::Point> NearestIntersection(const Geometry::Ray& ray) const;
        Colour Colour() const noexcept { return colour; }
    };
}
