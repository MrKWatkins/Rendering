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
        std::vector<std::shared_ptr<SceneObject>> objects;
        std::vector<std::shared_ptr<Light>> lights;
        Colour background;
        Colour ambientLight;

    public:
        explicit Scene(Colour background, Colour ambientLight);
        Scene& AddPlane(Geometry::Plane plane, Colour colour);
        Scene& AddSphere(Geometry::Sphere sphere, Colour colour);
        Scene& AddPointLight(Colour colour, Geometry::Point position);

        std::vector<std::shared_ptr<SceneObject>> Objects() const noexcept { return objects; }
        std::vector<std::shared_ptr<Light>> Lights() const noexcept { return lights; }
        Colour Background() const noexcept { return background; }
        Colour AmbientLight() const noexcept { return ambientLight; }
    };
}