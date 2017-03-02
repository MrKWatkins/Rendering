#include "stdafx.h"
#include "Lambertian.h"
#include <algorithm>

namespace MrKWatkins::Rendering::Shading
{
    Colour Lambertian::ShadePoint(Scene::Scene& scene, Scene::SceneObject& sceneObject, Geometry::Intersection& intersection) const
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

            auto intensity = std::clamp(lightRay.Direction().Dot(intersection.Normal()), 0.0, 1.0);

            colour = colour + sceneObject.Colour() * light->Colour() * intensity;
        }

        return colour;
    }
}
