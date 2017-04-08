#pragma once
#include "Solid.h"
#include "Intersection.h"
#include "Triangle.h"
#include "ObjFile.h"
#include "AxisAlignedBox.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Mesh final : public Solid
	{
		std::vector<Triangle> triangles;
		AxisAlignedBox boundingBox;
	public:
		explicit Mesh(const std::vector<Triangle>& triangles);
		explicit Mesh(const ObjFile& objFile);
		Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup);

		std::optional<Intersection> NearestIntersection(const Ray& ray) const override;

		static Mesh LoadObjFile(const std::wstring path);
	};
}
