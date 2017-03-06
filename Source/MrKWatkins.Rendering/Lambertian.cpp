#include "stdafx.h"
#include "Lambertian.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Lambertian::ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const
    {
        auto objectColour = sceneObject.GetColourAtPoint(intersection.Point());
        auto colour = objectColour * scene.AmbientLight();

        // Loop over all the lights in the scene to get their contribution.
        for (auto&& light : scene.Lights())
        {
            auto intensity = light->GetIntensityAtPoint(intersection.Point());
            if (intensity == 0)
            {
                continue;
            }

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

            // Lambertian reflectance is:
            // C = L.N Cs Cl I
            // Where:
            //  C  = Final colour.
            //  L  = Normal vector from surface to light.
            //  N  = Surface normal.
            //  Cs = Colour of surface at the point.
            //  Cl = Colour of light.
            //  I  = Intensity of light at the point.

            // Our ray (R) is from the light to the surface, i.e. R = -L. Therefore C = -R.N Cs Cl I
            auto lambertian = -lightRay.Direction().Dot(intersection.SurfaceNormal()) * objectColour * light->Colour() * intensity;

            colour = colour + lambertian;
        }

        return colour;
    }
}
