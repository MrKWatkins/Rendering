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
        Colour ambientLight;
        std::shared_ptr<Material> background;

    public:
        explicit Scene(const Colour& ambientLight);
        Scene(const Colour& ambientLight, const Colour& backgroundColour);
        Scene(const Colour& ambientLight, const std::shared_ptr<Material> background);

        Scene& AddPlane(const Plane& plane, const Colour& colour);
        Scene& AddPlane(const Plane& plane, const std::shared_ptr<Material> material);

        Scene& AddSphere(const Sphere& sphere, const Colour& colour);
        Scene& AddSphere(const Sphere& sphere, const std::shared_ptr<Material> material);

        Scene& AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour);

        const std::vector<std::unique_ptr<SceneObject>>& Objects() const noexcept { return objects; }
        const std::vector<std::unique_ptr<Light>>& Lights() const noexcept { return lights; }

        Colour GetBackground(const Ray& ray) const;

        const Colour& AmbientLight() const noexcept { return ambientLight; }
    };
}
