#pragma once
#include "Light.h"
#include "Object.h"
#include "ObjectIntersection.h"
#include "Flat.h"

using namespace MrKWatkins::Rendering::Geometry;
using namespace MrKWatkins::Rendering::Lighting;

namespace MrKWatkins::Rendering::Scene
{
    class Scene final
    {
        std::vector<std::unique_ptr<Object>> objects;
        std::vector<std::unique_ptr<Light>> lights;
        Colour ambientLight;
        std::shared_ptr<Texture> background;

    public:
        explicit Scene(const Colour& ambientLight);
        Scene(const Colour& ambientLight, const Colour& backgroundColour);
        Scene(const Colour& ambientLight, const std::shared_ptr<Texture> background);

		template<typename TTexture, class... TConstructorArguments>
		static std::shared_ptr<Texture> Create(TConstructorArguments&&... constructorArguments)
		{
			static_assert(std::is_base_of<Texture, TTexture>::value, "TTexture is not an instance of Texture.");

			return std::shared_ptr<Texture>(new TTexture(std::forward<TConstructorArguments>(constructorArguments)...));
		}

		template<typename TSolid>
		Scene& Add(const TSolid& solid, const Material& material)
		{
			static_assert(std::is_base_of<Solid, TSolid>::value, "TSolid is not an instance of Solid.");

			return Add(solid, std::shared_ptr<Texture>(std::make_shared<Flat>(material)));
		}

		template<typename TSolid>
		Scene& Add(const TSolid& solid, const std::shared_ptr<Texture> texture)
		{
			static_assert(std::is_base_of<Solid, TSolid>::value, "TSolid is not an instance of Solid.");

			auto pointerToSolid = std::unique_ptr<Solid>(std::make_unique<TSolid>(solid));
			auto pointerToSceneObject = std::make_unique<Object>(move(pointerToSolid), texture);
			objects.push_back(move(pointerToSceneObject));

			return *this;
		}

        Scene& AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour);

        const std::vector<std::unique_ptr<Object>>& Objects() const noexcept { return objects; }
        const std::vector<std::unique_ptr<Light>>& Lights() const noexcept { return lights; }

		std::unique_ptr<ObjectIntersection> GetClosestIntersection(const Ray& ray, const std::optional<const Object*> exclude = std::optional<const Object*>()) const;

		Colour GetBackground(const Ray& ray) const;

        const Colour& AmbientLight() const noexcept { return ambientLight; }
    };
}
