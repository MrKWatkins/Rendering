#include "stdafx.h"
#include "Colour.h"
#include "Sphere.h"
#include "Scene.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Scene
{
    Scene::Scene(const Colour& background, const Colour& ambientLight) : background{ background }, ambientLight { ambientLight }
    {
    }

    Scene& Scene::AddPlane(const Plane& plane, const Colour& colour)
    {
        auto pointerToPlane = std::unique_ptr<Object>(std::make_unique<Plane>(plane));
        auto pointerToSceneObject = std::make_unique<SceneObject>(move(pointerToPlane), colour);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddSphere(const Sphere& sphere, const Colour& colour)
    {
        auto pointerToSphere = std::unique_ptr<Object>(std::make_unique<Sphere>(sphere));
        auto pointerToSceneObject = std::make_unique<SceneObject>(move(pointerToSphere), colour);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour)
    {
        lights.push_back(std::make_unique<PointLight>(colour, attenuation, position));

        return *this;
    }
}
