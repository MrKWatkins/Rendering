#include "stdafx.h"
#include "RayTracing.h"

namespace MrKWatkins::Rendering::Algorithms
{
    RayTracing::RayTracing(std::unique_ptr<Scene::Scene>&& scene) : scene{move(scene)}
    {
    }

    Colour RayTracing::RenderPoint(double x, double y)
    {
        // Create a ray from the (x,y) point at 0 on the z-axis directed into positive z.
        auto ray = Geometry::Ray(Geometry::Point(x, y, 0), Geometry::Vector(0, 0, 1));

        auto colour = scene->Background();
        auto distanceToClosestIntersect = std::numeric_limits<double>::max();
        for (auto&& object : scene->Objects())
        {
            auto intersect = object->NearestIntersection(ray);
            if (!intersect.HasValue())
            {
                continue;
            }

            auto distanceToIntersect = ray.Origin().DistanceFrom(intersect.Value());
            if (distanceToIntersect < distanceToClosestIntersect)
            {
                distanceToClosestIntersect = distanceToIntersect;
                colour = object->Colour();
            }
        }

        return colour;
    }
}
