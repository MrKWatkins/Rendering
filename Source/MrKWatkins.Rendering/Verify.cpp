#include "stdafx.h"
#include "Vector.h"

namespace MrKWatkins::Rendering::Verify
{
	void IsNormalized(const Geometry::Vector& value, const std::string& parameterName)
	{
		if (!value.IsNormalized())
		{
			throw std::invalid_argument("Value of " + parameterName + " is not normalized.");
		}
	}
}