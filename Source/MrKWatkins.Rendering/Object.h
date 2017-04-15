#pragma once
#include "Solid.h"
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

		const Solid& Solid() const noexcept { return *solid; }

		Material GetMaterialAtPoint(const Point& point) const;
    };
}
