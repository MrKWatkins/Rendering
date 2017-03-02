#pragma once
#include <vector>
#include <memory>
#include "SceneObject.h"
#include "Sphere.h"
#include "Light.h"

namespace MrKWatkins::Rendering::Scene
{
    class Scene
    {
        std::vector<std::shared_ptr<SceneObject>> objects;
        std::vector<std::shared_ptr<Light>> lights;
        Colour background;

    public:
        explicit Scene(Colour background);
        Scene& AddSphere(Geometry::Sphere sphere, Colour colour);
        Scene& AddPointLight(Colour colour, Geometry::Point position);

        std::vector<std::shared_ptr<SceneObject>> Objects() const noexcept { return objects; }
        Colour Background() const noexcept { return background; }
    };
}
