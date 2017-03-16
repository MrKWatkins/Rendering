#include "stdafx.h"
#include "Material.h"

namespace MrKWatkins::Rendering
{
	Material::Material(const Colour& matte) : Material(matte, Colour::Black(), 0)
	{
	}

	Material::Material(const Colour& matte, double shininess) : Material(matte, Colour::White(), shininess)
	{
	}

	Material::Material(const Colour& matte, const Colour& specular, double shininess) : Material(matte, matte, specular, shininess)
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse, const Colour & specular, double shininess) : ambient{ ambient }, diffuse { diffuse }, specular{ specular }, shininess { shininess }
	{
	}
}