#pragma once
#include "Colour.h"
#include "Intersection.h"
#include "Scene.h"

using namespace MrKWatkins::Rendering::Scene;

namespace MrKWatkins::Rendering::Shading
{
	// TODO: Shading model should be on a per object level, ideally with a default at ray tracer level.
    class ShadingModel
    {
    public:
		template<typename TShadingModel, class... TConstructorArguments>
		static std::unique_ptr<ShadingModel> Create(TConstructorArguments&&... constructorArguments)
		{
			static_assert(std::is_base_of<ShadingModel, TShadingModel>::value, "TShadingModel is not an instance of ShadingModel.");

			return std::unique_ptr<ShadingModel>(new TShadingModel(std::forward<TConstructorArguments>(constructorArguments)...));
		}

        virtual ~ShadingModel() = default;

        virtual Colour ShadePoint(const Scene::Scene& scene, const Object& sceneObject, const Intersection& intersection) const = 0;
    };
}
