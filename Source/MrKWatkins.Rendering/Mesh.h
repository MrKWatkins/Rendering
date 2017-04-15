#pragma once
#include "Solid.h"
#include "Triangle.h"
#include "ObjFile.h"
#include "AxisAlignedBox.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Matrix;

	class Mesh final : public Solid
	{
		std::vector<Triangle> triangles;
		AxisAlignedBox boundingBox;
	public:
		explicit Mesh(const std::vector<Triangle>& triangles);
		explicit Mesh(const IO::ObjFile& objFile);
		Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup);

		std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const override;

		/// <summary>
		/// Generates a copy of the mesh with bounding box moved so that the the minimum is at the origin and the maximum has it's largest axis at 1.
		/// </summary>
		Mesh Normalize() const;

		Mesh Transform(const Matrix& transformation) const;

		static Mesh LoadObjFile(const std::wstring path);
	};
}
