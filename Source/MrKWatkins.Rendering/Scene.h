#pragma once
#include "Light.h"
#include "Plane.h"
#include "Object.h"
#include "ObjectIntersection.h"
#include "Sphere.h"

using namespace MrKWatkins::Rendering::Geometry;
using namespace MrKWatkins::Rendering::Lighting;

namespace MrKWatkins::Rendering::Scene
{
    class Scene final
    {
        std::vector<std::unique_ptr<Object>> objects;
        std::vector<std::unique_ptr<Light>> lights;
        Colour ambientLight;
        std::shared_ptr<Texture> background;

    public:
        explicit Scene(const Colour& ambientLight);
        Scene(const Colour& ambientLight, const Colour& backgroundColour);
        Scene(const Colour& ambientLight, const std::shared_ptr<Texture> background);

        Scene& AddPlane(const Plane& plane, const Material& material);
        Scene& AddPlane(const Plane& plane, const std::shared_ptr<Texture> texture);

        Scene& AddSphere(const Sphere& sphere, const Material& material);
        Scene& AddSphere(const Sphere& sphere, const std::shared_ptr<Texture> texture);

        Scene& AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour);

        const std::vector<std::unique_ptr<Object>>& Objects() const noexcept { return objects; }
        const std::vector<std::unique_ptr<Light>>& Lights() const noexcept { return lights; }

		std::optional<ObjectIntersection> GetClosestIntersection(const Ray& ray, const std::optional<const Object*> exclude = std::optional<const Object*>()) const;

		Colour GetBackground(const Ray& ray) const;

        const Colour& AmbientLight() const noexcept { return ambientLight; }
    };
}
