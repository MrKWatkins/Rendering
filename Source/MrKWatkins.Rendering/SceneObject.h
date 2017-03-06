#pragma once
#include "Object.h"
#include <memory>
#include "Colour.h"
#include "Intersection.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Scene
{
    class SceneObject
    {
        int id;
        std::unique_ptr<Object> object;
        Colour colour;

    public:
        SceneObject(std::unique_ptr<Object>&& object, const Colour& colour);
        SceneObject(const SceneObject& toCopy) = delete;
        ~SceneObject() = default;

        bool operator==(const SceneObject& other) const;
        bool operator!=(const SceneObject& other) const;

        Intersection NearestIntersection(const Ray& ray) const;
        const Colour& Colour() const noexcept { return colour; }
    };
}
