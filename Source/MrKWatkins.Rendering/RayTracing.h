#pragma once
#include <memory>
#include "Algorithm.h"
#include "Scene.h"
#include "Object.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Algorithms
{
    class RayTracing final : public Algorithm
    {
        std::unique_ptr<Shading::ShadingModel> shadingModel;
        std::unique_ptr<Scene::Scene> scene;

		// TODO: Camera should be in scene, along with something describing the view portal.
        Point camera;

		Colour CalculateColour(const Ray& ray, const std::optional<Scene::Object*> sourceObject, int recursionDepth);
    public:
        RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance);

        ~RayTracing() = default;

        Colour RenderPoint(double x, double y) override;
    };
}
