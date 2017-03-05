#include "stdafx.h"
#include "Lambertian.h"
#include <algorithm>

namespace MrKWatkins::Rendering::Shading
{
    Colour Lambertian::ShadePoint(const Scene::Scene& scene, const Scene::SceneObject& sceneObject, const Geometry::Intersection& intersection) const
    {
        auto colour = sceneObject.Colour() * scene.AmbientLight();

        // Loop over all the lights in the scene to get their contribution.
        for (auto&& light : scene.Lights())
        {
            auto lightRay = light->GetLightRayToPoint(intersection.Point());

            // Is there an object in between the source of the light and the intersection point?
            auto closerObject = false;
            auto distanceFromIntersection = lightRay.Origin().DistanceFrom(intersection.Point());
            for (auto&& object : scene.Objects())
            {
                if (*object == sceneObject)
                {
                    continue;
                }

                auto objectIntersection = object->NearestIntersection(lightRay);
                if (!objectIntersection.HasIntersection())
                {
                    continue;
                }

                auto distanceToObject = lightRay.Origin().DistanceFrom(objectIntersection.Point());
                if (distanceToObject < distanceFromIntersection)
                {
                    closerObject = true;
                    break;
                }
            }

            // If there is an object closer than the one we're calculating light for then it must be blocking the light.
            if (closerObject)
            {
                continue;
            }

            // Our ray is in the opposite direction to the surface normal - to calculate our intensity we need to flip the direction
            // of one of the vectors. However a cheaper operation will be to just negate the value afterwards.
            auto intensity = -lightRay.Direction().Dot(intersection.SurfaceNormal());

            colour = colour + sceneObject.Colour() * light->Colour() * intensity;
        }

        return colour;
    }
}
