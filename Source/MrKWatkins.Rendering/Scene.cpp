#include "stdafx.h"
#include "Colour.h"
#include "Sphere.h"
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

    Scene& Scene::AddPlane(const Plane& plane, const Material& material)
    {
        return AddPlane(plane, std::shared_ptr<Texture>(std::make_shared<Flat>(material)));
    }

    Scene& Scene::AddPlane(const Plane& plane, const std::shared_ptr<Texture> texture)
    {
        auto pointerToPlane = std::unique_ptr<Solid>(std::make_unique<Plane>(plane));
        auto pointerToSceneObject = std::make_unique<Object>(move(pointerToPlane), texture);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddSphere(const Sphere& sphere, const Material& material)
    {
        return AddSphere(sphere, std::shared_ptr<Texture>(std::make_shared<Flat>(material)));
    }

    Scene& Scene::AddSphere(const Sphere& sphere, const std::shared_ptr<Texture> texture)
    {
        auto pointerToSphere = std::unique_ptr<Solid>(std::make_unique<Sphere>(sphere));
        auto pointerToSceneObject = std::make_unique<Object>(move(pointerToSphere), texture);
        objects.push_back(move(pointerToSceneObject));

        return *this;
    }

    Scene& Scene::AddPointLight(const Point& position, const Attenuation& attenuation, const Colour& colour)
    {
        lights.push_back(std::make_unique<PointLight>(colour, attenuation, position));

        return *this;
    }

	std::optional<ObjectIntersection> Scene::GetClosestIntersection(const Ray & ray, const std::optional<const Object*> exclude) const
	{
		auto closest = std::optional<ObjectIntersection>();
		auto distanceToClosest = std::numeric_limits<double>::max();

		for (auto const& object : objects)
		{
			if (exclude.has_value() && *exclude.value() == *object)
			{
				continue;
			}

			auto intersection = object->NearestIntersection(ray);
			if (!intersection.has_value())
			{
				continue;
			}

			// TODO: Compare Length ^ 2 to avoid sqrts.
			auto distance = ray.Origin().DistanceFrom(intersection.value().Point());
			if (distance < distanceToClosest)
			{
				closest = ObjectIntersection(object.get(), intersection.value());
				distanceToClosest = distance;
			}
		}

		return closest;
	}

	Colour Scene::GetBackground(const Ray& ray) const
    {
        return background->GetMaterialAtPoint(Point(ray.Origin() + 10000000000 * ray.Direction())).Ambient();
    }
}
