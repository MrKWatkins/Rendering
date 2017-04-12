#pragma once
#include "Solid.h"
#include "Triangle.h"
#include "ObjFile.h"
#include "AxisAlignedBox.h"
#include "RayIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Matrix;

	class Mesh final : public Solid
	{
		std::vector<Triangle> triangles;
		AxisAlignedBox boundingBox;
	public:
		explicit Mesh(const std::vector<Triangle>& triangles);
		Mesh(const IO::ObjFile& objFile);
		Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup);

		/// <summary>
		/// Generates a copy of the mesh with bounding box moved so that the the minimum is at the origin and the maximum has it's largest axis at 1.
		/// </summary>
		Mesh Normalize() const;

		Mesh Transform(const Matrix& transformation) const;

		std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const override;

		static Mesh LoadObjFile(const std::wstring path);

		Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const override;
	};
}
