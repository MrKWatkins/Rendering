#pragma once
#include "Algorithm.h"
#include "Scene.h"
#include "ObjectIntersection.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Algorithms
{
    class RayTracing final : public Algorithm
    {
        std::unique_ptr<Shading::ShadingModel> shadingModel;
        std::unique_ptr<Scene::Scene> scene;
		int maximumRecursionDepth;

		// TODO: Camera should be in scene, along with something describing the view portal.
        Point camera;

		Colour CalculateColour(const Ray& ray, const std::optional<Scene::ObjectIntersection> previousIntersection, int recursionDepth) const;

		Colour CalculateDirectLight(const Material& material, const Scene::ObjectIntersection intersection) const;

		Colour CalculateReflection(const Ray& ray, const Material& material, const Scene::ObjectIntersection intersection, int recursionDepth) const;
    public:
        RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance, int maximumRecursionDepth = 100);

        ~RayTracing() = default;

        Colour RenderPoint(double x, double y) const override;
    };
}
