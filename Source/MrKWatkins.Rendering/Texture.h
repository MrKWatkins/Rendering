#pragma once
#include <memory>
#include "Colour.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Textures
{
    class Texture
    {
    public:
		template<typename TTexture, class... TConstructorArguments>
		static std::shared_ptr<Texture> Create(TConstructorArguments&&... constructorArguments)
		{
			static_assert(std::is_base_of<Texture, TTexture>::value, "TTexture is not an instance of Texture.");

			return std::shared_ptr<Texture>(new TTexture(std::forward<TConstructorArguments>(constructorArguments)...));
		}

        virtual ~Texture() = default;

        virtual Colour GetColourAtPoint(const Geometry::Point& point) const = 0;

    };
}
