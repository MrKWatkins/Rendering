#include "stdafx.h"
#include "RayTracing.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Algorithms
{
    RayTracing::RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene, double cameraDistance) : shadingModel{ move(shadingModel) }, scene { move(scene) }, camera(0.5, 0.5, -cameraDistance)
    {
    }

    Colour RayTracing::RenderPoint(double x, double y)
    {
        // Create a ray from the (x,y) point at 0 on the z-axis. It should point from the camera
        auto rayOrigin = Point(x, y, 0);
        auto ray = Ray(rayOrigin, rayOrigin - camera);

		auto intersection = scene->GetClosestIntersection(ray);

        if (!intersection.has_value())
        {
            return scene->GetBackground(ray);
        }

        return shadingModel->ShadePoint(*scene, *intersection.value().Object(), intersection.value());
    }
}
