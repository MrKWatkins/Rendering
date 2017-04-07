#pragma once
#include "Solid.h"
#include "Intersection.h"
#include "Triangle.h"
#include "ObjFile.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Mesh final : public Solid
	{
		std::vector<Triangle> triangles;
	public:
		Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup);
		explicit Mesh(const std::vector<Triangle>& triangles);
		explicit Mesh(const ObjFile& objFile);

		std::optional<Intersection> NearestIntersection(const Ray& ray) const override;

		static Mesh LoadObjFile(const std::wstring path);
	};
}
