#include "stdafx.h"
#include "Lambertian.h"

namespace MrKWatkins::Rendering::Shading
{
    Colour Lambertian::ShadePoint(const Scene::Scene& scene, const SceneObject& sceneObject, const Intersection& intersection) const
    {
        auto objectMaterial = sceneObject.GetMaterialAtPoint(intersection.Point());
        auto colour = objectMaterial.Ambient() * scene.AmbientLight();

        // Loop over all the lights in the scene to get their contribution.
        for (auto&& light : scene.Lights())
        {
            auto intensity = light->GetIntensityAtPoint(intersection.Point());
            if (intensity == 0)
            {
                continue;
            }

            auto lightRay = light->GetLightRayToPoint(intersection.Point());
			if (IsRayToPointOnObjectBlocked(scene, lightRay, sceneObject, intersection.Point()))
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
            auto lambertian = -lightRay.Direction().Dot(intersection.SurfaceNormal()) * objectMaterial.Diffuse() * light->Colour() * intensity;

            colour = colour + lambertian;
        }

        return colour;
    }
}
