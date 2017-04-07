#pragma once
#include "Triangle.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering
{
	// TODO: Probably shouldn't be copyable.
	class ObjFile
	{
		mutable std::vector<Triangle> triangles;

		ObjFile();
	public:

		const std::vector<Triangle>& Triangles() const noexcept { return triangles; }

		static ObjFile Load(const std::wstring& path);
	};
}
