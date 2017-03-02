#include "stdafx.h"
#include "Lambertian.h"
#include <algorithm>

namespace MrKWatkins::Rendering::Shading
{
    Colour Lambertian::ShadePoint(Scene::Scene& scene, Geometry::Point point, Colour colourOfPoint, Geometry::Vector surfaceNormal) const
    {
        auto colour = Colour(0, 0, 0);

        // Loop over all the lights in the scene to get their contribution.
        for (auto&& light : scene.Lights())
        {
            auto lightDirection = light->GetDirectionAtPoint(point, surfaceNormal).Normalize();

            auto intensity = std::clamp(lightDirection.Dot(surfaceNormal), 0.0, 1.0);

            colour = colour + colourOfPoint * light->Colour() * intensity;
        }

        return colour;
    }
}
