#pragma once
#include "Colour.h"

namespace MrKWatkins::Rendering
{
	// TODO: No specular should have specular colour black rather than shininess 0.
	class Material final
	{
		Colour diffuse;
		Colour specular;
		Colour ambient;
		double shininess;
	public:
		/// <summary>
		/// Initializes an instance of a perfectly matte material.
		/// </summary>
		explicit Material(const Colour& matte);

		/// <summary>
		/// Initializes an instance of a material with white specular highlights.
		/// </summary>
		Material(const Colour& matte, double shininess);

		/// <summary>
		/// Initializes an instance of a material.
		/// </summary>
		Material(const Colour& matte, const Colour& specular, double shininess);
		
		/// <summary>
		/// Initializes an instance of a material with separate diffuse and ambient colours.
		/// </summary>
		Material(const Colour& ambient, const Colour& diffuse, const Colour& specular, double shininess);

		const Colour& Specular() const noexcept { return specular; }
		const Colour& Diffuse() const noexcept { return diffuse; }
		const Colour& Ambient() const noexcept { return ambient; }
		double Shininess() const noexcept { return shininess; }
	};
}
