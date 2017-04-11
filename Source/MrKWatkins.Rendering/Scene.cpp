#include "stdafx.h"
#include "Colour.h"
#include "Scene.h"
#include "PointLight.h"
#include "Flat.h"

namespace MrKWatkins::Rendering::Scene
{
    Scene::Scene(const Colour& ambientLight) : Scene(ambientLight, Colour(0, 0, 0))
    {
    }

    Scene::Scene(const Colour& ambientLight, const Colour& backgroundColour) : Scene(ambientLight, std::shared_ptr<Texture>(std::make_shared<Flat>(Material(backgroundColour))))
    {
    }

    Scene::Scene(const Colour& ambientLight, const std::shared_ptr<Texture> background) : ambientLight{ ambientLight }, background { background }
    {
    }

	Scene& Scene::AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour)
    {
        lights.push_back(std::make_unique<PointLight>(colour, attenuation, position));

        return *this;
    }

	std::optional<ObjectIntersection> Scene::GetClosestIntersection(const Ray & ray, const std::optional<const Object*> exclude) const
	{
		Object* closestObject = nullptr;
		auto closestRayIntersection = std::optional<RayIntersection>();

		for (auto const& object : objects)
		{
			if (exclude.has_value() && *exclude.value() == *object)
			{
				continue;
			}

			auto rayIntersection = object->Solid().NearestRayIntersection(ray);
			if (!rayIntersection.has_value())
			{
				continue;
			}

			if (!closestRayIntersection.has_value() || rayIntersection->D() < closestRayIntersection->D())
			{
				closestObject = object.get();
				closestRayIntersection = rayIntersection;
			}
		}

		if (closestRayIntersection.has_value())
		{
			return ObjectIntersection(closestObject->Solid().GetSurfaceIntersection(ray, closestRayIntersection.value()), closestObject);
		}

		return std::optional<ObjectIntersection>();
	}

	Colour Scene::GetBackground(const Ray& ray) const
    {
        return background->GetMaterialAtPoint(Point(ray.Origin() + 10000000000 * ray.Direction())).Ambient();
    }
}
