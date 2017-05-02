#include "stdafx.h"
#include "Lambertian.h"

namespace MrKWatkins::Rendering::Materials
{
	Lambertian::Lambertian(const Colour& colour) : colour { colour }
	{
	}

	Colour Lambertian::Evaluate(const Vector& incoming, const Intersection& intersection, const Vector& outgoing) const
	{
		return colour;
	}
}