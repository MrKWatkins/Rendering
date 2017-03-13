#pragma once
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Shading
{
	class Phong final : public ShadingModel
	{
	public:
		Colour ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const override;
	};
}
