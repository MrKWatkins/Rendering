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
		double reflectivity;
	public:
		/// <summary>
		/// Initializes an instance of a perfectly matte material.
		/// </summary>
		explicit Material(const Colour& matte);

		/// <summary>
		/// Initializes an instance of a material with white specular highlights.
		/// </summary>
		Material(const Colour& matte, double shininess, double reflectivity);

		/// <summary>
		/// Initializes an instance of a material.
		/// </summary>
		Material(const Colour& matte, const Colour& specular, double shininess, double reflectivity);

		/// <summary>
		/// Initializes an instance of a material with separate diffuse and ambient colours.
		/// </summary>
		Material(const Colour& ambient, const Colour& diffuse, const Colour& specular, double shininess, double reflectivity);

		const Colour& Specular() const noexcept { return specular; }
		const Colour& Diffuse() const noexcept { return diffuse; }
		const Colour& Ambient() const noexcept { return ambient; }
		double Shininess() const noexcept { return shininess; }
		double Reflectivity() const noexcept { return reflectivity; }

		// Definitions from http://devernay.free.fr/cours/opengl/materials.html.
		static Material Emerald() noexcept { return Material(Colour(0.0215, 0.1745, 0.0215), Colour(0.07568, 0.61424, 0.07568), Colour(0.633, 0.727811, 0.633), 0.6 * 128, 0); }
		static Material Jade() noexcept { return Material(Colour(0.135, 0.2225, 0.1575), Colour(0.54, 0.89, 0.63), Colour(0.316228, 0.316228, 0.316228), 0.1 * 128, 0); }
		static Material	Obsidian() noexcept { return Material(Colour(0.05375, 0.05, 0.06625), Colour(0.18275, 0.17, 0.22525), Colour(0.332741, 0.328634, 0.346435), 0.3 * 128, 0); }
		static Material	Pearl() noexcept { return Material(Colour(0.25, 0.20725, 0.20725), Colour(1, 0.829, 0.829), Colour(0.296648, 0.296648, 0.296648), 0.088 * 128, 0); }
		static Material	Ruby() noexcept { return Material(Colour(0.1745, 0.01175, 0.01175), Colour(0.61424, 0.04136, 0.04136), Colour(0.727811, 0.626959, 0.626959), 0.6 * 128, 0); }
		static Material	Turquoise() noexcept { return Material(Colour(0.1, 0.18725, 0.1745), Colour(0.396, 0.74151, 0.69102), Colour(0.297254, 0.30829, 0.306678), 0.1 * 128, 0); }
		static Material	Brass() noexcept { return Material(Colour(0.329412, 0.223529, 0.027451), Colour(0.780392, 0.568627, 0.113725), Colour(0.992157, 0.941176, 0.807843), 0.21794872 * 128, 0); }
		static Material	Bronze() noexcept { return Material(Colour(0.2125, 0.1275, 0.054), Colour(0.714, 0.4284, 0.18144), Colour(0.393548, 0.271906, 0.166721), 0.2 * 128, 0); }
		static Material	Chrome() noexcept { return Material(Colour(0.25, 0.25, 0.25), Colour(0.4, 0.4, 0.4), Colour(0.774597, 0.774597, 0.774597), 0.6 * 128, 0.7); }
		static Material	Copper() noexcept { return Material(Colour(0.19125, 0.0735, 0.0225), Colour(0.7038, 0.27048, 0.0828), Colour(0.256777, 0.137622, 0.086014), 0.1 * 128, 0); }
		static Material	Gold() noexcept { return Material(Colour(0.24725, 0.1995, 0.0745), Colour(0.75164, 0.60648, 0.22648), Colour(0.628281, 0.555802, 0.366065), 0.4 * 128, 0); }
		static Material	Silver() noexcept { return Material(Colour(0.19225, 0.19225, 0.19225), Colour(0.50754, 0.50754, 0.50754), Colour(0.508273, 0.508273, 0.508273), 0.4 * 128, 0); }
		static Material	BlackPlastic() noexcept { return Material(Colour(0.0, 0.0, 0.0), Colour(0.01, 0.01, 0.01), Colour(0.50, 0.50, 0.50), 0.25 * 128, 0); }
		static Material	CyanPlastic() noexcept { return Material(Colour(0.0, 0.1, 0.06), Colour(0.0, 0.50980392, 0.50980392), Colour(0.50196078, 0.50196078, 0.50196078), 0.25 * 128, 0); }
		static Material	GreenPlastic() noexcept { return Material(Colour(0.0, 0.0, 0.0), Colour(0.1, 0.35, 0.1), Colour(0.45, 0.55, 0.45), 0.25 * 128, 0); }
		static Material	RedPlastic() noexcept { return Material(Colour(0.0, 0.0, 0.0), Colour(0.5, 0.0, 0.0), Colour(0.7, 0.6, 0.6), 0.25 * 128, 0); }
		static Material	WhitePlastic() noexcept { return Material(Colour(0.0, 0.0, 0.0), Colour(0.55, 0.55, 0.55), Colour(0.70, 0.70, 0.70), 0.25 * 128, 0); }
		static Material	YellowPlastic() noexcept { return Material(Colour(0.0, 0.0, 0.0), Colour(0.5, 0.5, 0.0), Colour(0.60, 0.60, 0.50), 0.25 * 128, 0); }
		static Material	BlackRubber() noexcept { return Material(Colour(0.02, 0.02, 0.02), Colour(0.01, 0.01, 0.01), Colour(0.4, 0.4, 0.4), 0.078125 * 128, 0); }
		static Material	CyanRubber() noexcept { return Material(Colour(0.0, 0.05, 0.05), Colour(0.4, 0.5, 0.5), Colour(0.04, 0.7, 0.7), 0.078125 * 128, 0); }
		static Material	GreenRubber() noexcept { return Material(Colour(0.0, 0.05, 0.0), Colour(0.4, 0.5, 0.4), Colour(0.04, 0.7, 0.04), 0.078125 * 128, 0); }
		static Material	RedRubber() noexcept { return Material(Colour(0.05, 0.0, 0.0), Colour(0.5, 0.4, 0.4), Colour(0.7, 0.04, 0.04), 0.078125 * 128, 0); }
		static Material	WhiteRubber() noexcept { return Material(Colour(0.05, 0.05, 0.05), Colour(0.5, 0.5, 0.5), Colour(0.7, 0.7, 0.7), 0.078125 * 128, 0); }
		static Material	YellowRubber() noexcept { return Material(Colour(0.05, 0.05, 0.0), Colour(0.5, 0.5, 0.4), Colour(0.7, 0.7, 0.04), 0.078125 * 128, 0); }
	};
}
