#include "stdafx.h"
#include "Material.h"

namespace MrKWatkins::Rendering
{
	Material::Material(const Colour& matte) : Material(matte, Colour::Black(), 0, 0)
	{
	}

	Material::Material(const Colour& matte, double shininess, double reflectivity) : Material(matte, Colour::White(), shininess, reflectivity)
	{
	}

	Material::Material(const Colour& matte, const Colour& specular, double shininess, double reflectivity) : Material(matte, matte, specular, shininess, reflectivity)
	{
	}

	Material::Material(const Colour& ambient, const Colour& diffuse, const Colour & specular, double shininess, double reflectivity) : ambient{ ambient }, diffuse { diffuse }, specular{ specular }, shininess { shininess }, reflectivity { reflectivity }
	{
	}
}