#pragma once
#include <vector>
#include <memory>
#include "Light.h"
#include "Plane.h"
#include "SceneObject.h"
#include "Sphere.h"

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
        Scene& AddPlane(const Geometry::Plane& plane, const Colour& colour);
        Scene& AddSphere(const Geometry::Sphere& sphere, const Colour& colour);
        Scene& AddPointLight(const Geometry::Point& position, const Colour& colour);

        const std::vector<std::unique_ptr<SceneObject>>& Objects() const noexcept { return objects; }
        const std::vector<std::unique_ptr<Light>>& Lights() const noexcept { return lights; }
        const Colour& Background() const noexcept { return background; }
        const Colour& AmbientLight() const noexcept { return ambientLight; }
    };
}
