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

	std::unique_ptr<ObjectIntersection> Scene::GetClosestIntersection(const Ray & ray, const std::optional<const Object*> exclude) const
	{
		std::unique_ptr<ObjectIntersection> closestIntersection;

		for (auto const& object : objects)
		{
			if (exclude.has_value() && *exclude.value() == *object)
			{
				continue;
			}

			auto intersection = object->Solid().NearestIntersection(ray);
			if (intersection == nullptr)
			{
				continue;
			}

			if (closestIntersection == nullptr || intersection->DistanceAlongRay() < closestIntersection->Intersection()->DistanceAlongRay())
			{
				closestIntersection.reset(new ObjectIntersection(object.get(), move(intersection)));
			}
		}

		return closestIntersection;
	}

	Colour Scene::GetBackground(const Ray& ray) const
    {
        return background->GetMaterialAtPoint(Point(ray.Origin() + 10000000000 * ray.Direction())).Ambient();
    }
}
