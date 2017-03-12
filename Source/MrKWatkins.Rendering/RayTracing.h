#pragma once
#include <memory>
#include "Algorithm.h"
#include "Scene.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Algorithms
{
    class RayTracing final : public Algorithm
    {
        std::unique_ptr<Shading::ShadingModel> shadingModel;
        std::unique_ptr<Scene::Scene> scene;
        Point camera;
    public:
        RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance);

        ~RayTracing() = default;

        Colour RenderPoint(double x, double y) override;
    };
}
