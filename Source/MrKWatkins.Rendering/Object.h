#pragma once
#include <memory>
#include "Solid.h"
#include "Intersection.h"
#include "Texture.h"

using namespace MrKWatkins::Rendering::Geometry;
using namespace MrKWatkins::Rendering::Textures;

namespace MrKWatkins::Rendering::Scene
{
    class Object final
    {
        int id;
        std::unique_ptr<Solid> solid;
        std::shared_ptr<Texture> texture;

    public:
		Object(std::unique_ptr<Solid>&& solid, const std::shared_ptr<Texture> texture);
		Object(const Object& toCopy) = delete;
        ~Object() = default;

        bool operator==(const Object& other) const;
        bool operator!=(const Object& other) const;

		bool IsSphere() const { return solid->IsSphere(); }

		std::optional<Intersection> NearestIntersection(const Ray& ray) const;

		Material GetMaterialAtPoint(const Point& point) const;
    };
}
