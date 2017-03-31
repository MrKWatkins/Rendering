#include "stdafx.h"
#include "Material.h"
#include "Verify.h"

namespace MrKWatkins::Rendering
{
	Material::Material(const Colour& ambientAndDiffuse) : Material(ambientAndDiffuse, ambientAndDiffuse)
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse) : ambient{ ambient }, diffuse{ diffuse }
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse, const Colour& specular, double shininess, double reflectivity) : ambient{ ambient }, diffuse{ diffuse }, specular{ specular }, shininess{ shininess }, reflectivity{ reflectivity }
	{
		//Verify::GreaterThan(0.0, shininess, "shininess");
		VERIFY_ZERO_TO_ONE(reflectivity);
	}

	MaterialBuilder Material::Build(const Colour& ambientAndDiffuse)
	{
		return MaterialBuilder(ambientAndDiffuse);
	}

	MaterialBuilder Material::Build(const Colour& ambient, const Colour& diffuse)
	{
		return MaterialBuilder(ambient, diffuse);
	}

	MaterialBuilder Material::Build(const Material& baseMaterial)
	{
		return MaterialBuilder(baseMaterial);
	}

	MaterialBuilder::MaterialBuilder(const Colour& ambientAndDiffuse) : material(ambientAndDiffuse, ambientAndDiffuse)
	{
	}

	MaterialBuilder::MaterialBuilder(const Colour& ambient, const Colour& diffuse) : material(ambient, diffuse)
	{
	}

	MaterialBuilder::MaterialBuilder(const Material& baseMaterial) : material{ baseMaterial }
	{
	}

	MaterialBuilder& MaterialBuilder::WithSpecular(double shininess, const Colour& colour)
	{
		//Verify::GreaterThan(0.0, shininess, "shininess");

		material.shininess = shininess;
		material.specular = colour;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::WithReflectivity(double reflectivity)
	{
		VERIFY_ZERO_TO_ONE(reflectivity);

		if (reflectivity + material.transmittance > 1.0)
		{
			throw std::out_of_range("Reflectivity + transmittance must be in the range 0 -> 1.");
		}

		material.reflectivity = reflectivity;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::WithTransmittance(double transmittance, double refractiveIndex)
	{
		VERIFY_ZERO_TO_ONE(transmittance);

		if (material.reflectivity + transmittance > 1.0)
		{
			throw std::out_of_range("Reflectivity + transmittance must be in the range 0 -> 1.");
		}
		if (refractiveIndex == 0.0)
		{
			throw std::out_of_range("refractiveIndex cannot be 0.");
		}

		material.transmittance = transmittance;
		material.refractiveIndex = refractiveIndex;

		return *this;
	}
}
