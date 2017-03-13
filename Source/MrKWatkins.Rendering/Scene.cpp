#include "stdafx.h"
#include "Colour.h"
#include "Sphere.h"
#include "Scene.h"
#include "PointLight.h"
#include "Solid.h"

namespace MrKWatkins::Rendering::Scene
{
    Scene::Scene(const Colour& ambientLight) : Scene(ambientLight, Colour(0, 0, 0))
    {
    }

    Scene::Scene(const Colour& ambientLight, const Colour& backgroundColour) : Scene(ambientLight, std::shared_ptr<Texture>(std::make_shared<Solid>(Material(backgroundColour))))
    {
    }

    Scene::Scene(const Colour& ambientLight, const std::shared_ptr<Texture> background) : ambientLight{ ambientLight }, background { background }
    {
    }

    Scene& Scene::AddPlane(const Plane& plane, const Material& material)
    {
        return AddPlane(plane, std::shared_ptr<Texture>(std::make_shared<Solid>(material)));
    }

    Scene& Scene::AddPlane(const Plane& plane, const std::shared_ptr<Texture> texture)
    {
        auto pointerToPlane = std::unique_ptr<Object>(std::make_unique<Plane>(plane));
        auto pointerToSceneObject = std::make_unique<SceneObject>(move(pointerToPlane), texture);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddSphere(const Sphere& sphere, const Material& material)
    {
        return AddSphere(sphere, std::shared_ptr<Texture>(std::make_shared<Solid>(material)));
    }

    Scene& Scene::AddSphere(const Sphere& sphere, const std::shared_ptr<Texture> texture)
    {
        auto pointerToSphere = std::unique_ptr<Object>(std::make_unique<Sphere>(sphere));
        auto pointerToSceneObject = std::make_unique<SceneObject>(move(pointerToSphere), texture);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour)
    {
        lights.push_back(std::make_unique<PointLight>(colour, attenuation, position));

        return *this;
    }

    Colour Scene::GetBackground(const Ray& ray) const
    {
        return background->GetMaterialAtPoint(Point(ray.Origin() + 10000000000 * ray.Direction())).Ambient();
    }
}
