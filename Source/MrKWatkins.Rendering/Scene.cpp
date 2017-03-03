#include "stdafx.h"
#include "Colour.h"
#include "Sphere.h"
#include "Scene.h"
#include "PointLight.h"

namespace MrKWatkins::Rendering::Scene
{
    Scene::Scene(Colour background, Colour ambientLight) : background{ background }, ambientLight { ambientLight }
    {
    }

    Scene& Scene::AddPlane(Geometry::Plane plane, Colour colour)
    {
        auto pointerToPlane = std::unique_ptr<Geometry::Object>(std::make_unique<Geometry::Plane>(plane));
        auto pointerToSceneObject = std::make_shared<SceneObject>(move(pointerToPlane), colour);
        objects.push_back(pointerToSceneObject);

        return *this;
    }

    Scene& Scene::AddSphere(Geometry::Sphere sphere, Colour colour)
    {
        auto pointerToSphere = std::unique_ptr<Geometry::Object>(std::make_unique<Geometry::Sphere>(sphere));
        auto pointerToSceneObject = std::make_shared<SceneObject>(move(pointerToSphere), colour);
        objects.push_back(pointerToSceneObject);

        return *this;
    }

    Scene& Scene::AddPointLight(Colour colour, Geometry::Point position)
    {
        lights.push_back(std::make_shared<PointLight>(colour, position));

        return *this;
    }
}
