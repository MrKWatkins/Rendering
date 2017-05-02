#pragma once
#include "Colour.h"
#include "Intersection.h"
#include "Vector.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::Materials
{
	class Brdf
	{
	public:
		virtual ~Brdf() = default;

		virtual Colour Evaluate(const Vector& incoming, const Intersection& intersection, const Vector& outgoing) const = 0;
	};
}
