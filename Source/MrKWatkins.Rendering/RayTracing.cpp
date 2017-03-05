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
        auto rayOrigin = Geometry::Point(x, y, 0);
        auto ray = Geometry::Ray(rayOrigin, rayOrigin - camera);

        std::shared_ptr<Scene::SceneObject> closestObject;
        auto closestIntersection = Geometry::Intersection::None();
        auto distanceToClosestIntersection = std::numeric_limits<double>::max();

        for (auto&& object : scene->Objects())
        {
            auto intersection = object->NearestIntersection(ray);
            if (!intersection.HasIntersection())
            {
                continue;
            }

            auto distanceToIntersection = ray.Origin().DistanceFrom(intersection.Point());
            if (distanceToIntersection < distanceToClosestIntersection)
            {
                closestObject = object;
                closestIntersection = intersection;
                distanceToClosestIntersection = distanceToIntersection;
            }
        }

        if (!closestIntersection.HasIntersection())
        {
            return scene->Background();
        }

        return shadingModel->ShadePoint(*scene, *closestObject, closestIntersection);
    }
}
