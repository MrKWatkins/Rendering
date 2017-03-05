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

    Scene& Scene::AddPlane(const Geometry::Plane& plane, const Colour& colour)
    {
        auto pointerToPlane = std::unique_ptr<Geometry::Object>(std::make_unique<Geometry::Plane>(plane));
        auto pointerToSceneObject = std::make_shared<SceneObject>(move(pointerToPlane), colour);
        objects.push_back(pointerToSceneObject);

        return *this;
    }

    Scene& Scene::AddSphere(const Geometry::Sphere& sphere, const Colour& colour)
    {
        auto pointerToSphere = std::unique_ptr<Geometry::Object>(std::make_unique<Geometry::Sphere>(sphere));
        auto pointerToSceneObject = std::make_shared<SceneObject>(move(pointerToSphere), colour);
        objects.push_back(pointerToSceneObject);

        return *this;
    }

    Scene& Scene::AddPointLight(const Geometry::Point& position, const Colour& colour)
    {
        lights.push_back(std::make_shared<PointLight>(colour, position));

        return *this;
    }
}
