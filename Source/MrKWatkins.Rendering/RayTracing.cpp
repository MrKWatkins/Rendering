#include "stdafx.h"
#include "RayTracing.h"
#include "ShadingModel.h"

namespace MrKWatkins::Rendering::Algorithms
{
    RayTracing::RayTracing(std::unique_ptr<Shading::ShadingModel>&& shadingModel, std::unique_ptr<Scene::Scene>&& scene) : shadingModel{ move(shadingModel) }, scene { move(scene) }
    {
    }

    Colour RayTracing::RenderPoint(double x, double y)
    {
        // Create a ray from the (x,y) point at 0 on the z-axis directed into positive z.
        auto ray = Geometry::Ray(Geometry::Point(x, y, 0), Geometry::Vector(0, 0, 1));

        Colour colour;
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
                colour = object->Colour();
                closestIntersection = intersection;
                distanceToClosestIntersection = distanceToIntersection;
            }
        }

        if (!closestIntersection.HasIntersection())
        {
            return scene->Background();
        }

        return shadingModel->ShadePoint(*scene, closestIntersection.Point(), colour, closestIntersection.Normal());
    }
}
