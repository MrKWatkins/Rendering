#pragma once
#include "Brdf.h"

namespace MrKWatkins::Rendering::Materials
{
	class Lambertian final : public Brdf
	{
		Colour colour;
	public:
		explicit Lambertian(const Colour& colour);

		Colour Evaluate(const Vector& incoming, const Intersection& intersection, const Vector& outgoing) const override;
	};
}
