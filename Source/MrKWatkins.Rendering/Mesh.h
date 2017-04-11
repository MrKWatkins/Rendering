#pragma once
#include "Solid.h"
#include "Triangle.h"
#include "ObjFile.h"
#include "AxisAlignedBox.h"
#include "RayIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Mesh final : public Solid
	{
		std::vector<Triangle> triangles;
		AxisAlignedBox boundingBox;
	public:
		explicit Mesh(const std::vector<Triangle>& triangles);
		explicit Mesh(const IO::ObjFile& objFile);
		Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup);

		std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const override;

		static Mesh LoadObjFile(const std::wstring path);

		Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const override;
	};
}
