#pragma once
#include "Object.h"
#include <memory>
#include "Intersection.h"
#include "Texture.h"

using namespace MrKWatkins::Rendering::Geometry;
using namespace MrKWatkins::Rendering::Textures;

namespace MrKWatkins::Rendering::Scene
{
    class SceneObject final
    {
        int id;
        std::unique_ptr<Object> object;
        std::shared_ptr<Texture> texture;

    public:
        SceneObject(std::unique_ptr<Object>&& object, const std::shared_ptr<Texture> texture);
        SceneObject(const SceneObject& toCopy) = delete;
        ~SceneObject() = default;

        bool operator==(const SceneObject& other) const;
        bool operator!=(const SceneObject& other) const;

        Intersection NearestIntersection(const Ray& ray) const;

        Colour GetColourAtPoint(const Point& point) const;
    };
}
