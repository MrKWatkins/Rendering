#include "stdafx.h"
#include "Mesh.h"
#include "Verify.h"
#include "Matrix.h"

namespace MrKWatkins::Rendering::Geometry
{
	Mesh::Mesh(const std::vector<Triangle>& triangles) : triangles{ triangles }, boundingBox{ AxisAlignedBox::CreateBoundingBoxForTriangles(triangles) }
	{
	}

	Mesh::Mesh(const IO::ObjFile& objFile) : Mesh(objFile.Triangles())
	{
	}

	Mesh::Mesh(const std::vector<Point>& vertices, const std::vector<int>& triangleLookup) : triangles{}, boundingBox{ AxisAlignedBox::CreateBoundingBoxForPoints(vertices) }
	{
		VERIFY_GREATER_THAN(2, triangleLookup.size());

		for (auto f = 0; f<triangleLookup.size() - 2; f++)
		{
			triangles.push_back(Triangle(vertices[f], vertices[f + 1], vertices[f + 2]));
		}
	}

	Mesh Mesh::Normalize() const
	{
		return Transform(boundingBox.GetNormalizeTransform());
	}

	Mesh Mesh::Transform(const Matrix& transformation) const
	{
		std::vector<Triangle> transformedTriangles;
		for (auto& triangle : triangles)
		{
			transformedTriangles.push_back(triangle.Transform(transformation));
		}
		return Mesh(transformedTriangles);
	}

	std::optional<RayIntersection> Mesh::NearestRayIntersection(const Ray& ray) const
	{
		if (!boundingBox.Intersects(ray))
		{
			return std::optional<RayIntersection>();
		}

		auto nearestIntersection = std::optional<RayIntersection>();
		for (auto& triangle : triangles)
		{
			auto intersection = triangle.NearestRayIntersection(ray);
			if (intersection.has_value() &&
				(!nearestIntersection.has_value() || intersection->D() < nearestIntersection->D()))
			{
				nearestIntersection = RayIntersection(intersection.value(), &triangle);
			}
		}

		return nearestIntersection;
	}

	Mesh Mesh::LoadObjFile(const std::wstring path)
	{
		return Mesh(IO::ObjFile::Load(path));
	}

	Vector Mesh::GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const
	{
		return rayIntersection.ChildSolid()->GetSurfaceNormal(rayIntersection, pointOnSurface);
	}
}
