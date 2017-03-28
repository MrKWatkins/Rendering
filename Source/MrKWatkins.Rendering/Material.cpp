#include "stdafx.h"
#include "Material.h"

namespace MrKWatkins::Rendering
{
	// TODO: Parameter validation.

	Material::Material(const Colour& ambientAndDiffuse) : Material(ambientAndDiffuse, ambientAndDiffuse)
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse) : ambient{ ambient }, diffuse{ diffuse }
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse, const Colour& specular, double shininess, double reflectivity) : ambient{ ambient }, diffuse{ diffuse }, specular{ specular }, shininess{ shininess }, reflectivity{ reflectivity }
	{
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
		material.shininess = shininess;
		material.specular = colour;

		return *this;
	}

	MaterialBuilder& MaterialBuilder::WithReflectivity(double reflectivity)
	{
		material.reflectivity = reflectivity;

		return *this;
	}
}
