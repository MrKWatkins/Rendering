#pragma once
#include <vector>
#include <memory>
#include "Light.h"
#include "Plane.h"
#include "SceneObject.h"
#include "Sphere.h"

using namespace MrKWatkins::Rendering::Geometry;
using namespace MrKWatkins::Rendering::Lighting;

namespace MrKWatkins::Rendering::Scene
{
    class Scene
    {
        std::vector<std::unique_ptr<SceneObject>> objects;
        std::vector<std::unique_ptr<Light>> lights;
        Colour background;
        Colour ambientLight;

    public:
        explicit Scene(const Colour& background, const Colour& ambientLight);

        Scene& AddPlane(const Plane& plane, const Colour& colour);
        Scene& AddPlane(const Plane& plane, const std::shared_ptr<Material> material);

        Scene& AddSphere(const Sphere& sphere, const Colour& colour);
        Scene& AddSphere(const Sphere& sphere, const std::shared_ptr<Material> material);

        Scene& AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour);

        const std::vector<std::unique_ptr<SceneObject>>& Objects() const noexcept { return objects; }
        const std::vector<std::unique_ptr<Light>>& Lights() const noexcept { return lights; }
        const Colour& Background() const noexcept { return background; }
        const Colour& AmbientLight() const noexcept { return ambientLight; }
    };
}
