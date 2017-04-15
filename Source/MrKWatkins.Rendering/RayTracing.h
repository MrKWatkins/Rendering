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

		Colour CalculateColour(const Ray& ray, const Scene::ObjectIntersection* previousIntersection, int recursionDepth) const;

		Colour CalculateDirectLight(const Material& material, const Scene::ObjectIntersection* intersection) const;

		Colour CalculateReflection(const Ray& ray, double reflectivity, const Scene::ObjectIntersection* intersection, int recursionDepth) const;

		std::optional<Ray> CalculateExitRayForTransmittance(const Ray& refractedRay, const Material& material, const Scene::Object* object, int* recursionDepth) const;

		std::optional<Colour> CalculateTransmittance(const Ray& ray, const Material& material, const Scene::ObjectIntersection* intersection, int recursionDepth) const;
    public:
        RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance, int maximumRecursionDepth = 100);

        ~RayTracing() = default;

        Colour RenderPoint(double x, double y) const override;
    };
}
