#include "stdafx.h"
#include "Mesh.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Mesh::Mesh(const std::vector<Triangle>& triangles) : triangles{ triangles }, boundingBox{ AxisAlignedBox::CreateBoundingBoxForTriangles(triangles) }
	{
	}

	Mesh::Mesh(const ObjFile& objFile) : Mesh(objFile.Triangles())
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

	std::optional<Intersection> Mesh::NearestIntersection(const Ray& ray) const
	{
		if (!boundingBox.Intersects(ray))
		{
			return std::optional<Intersection>();
		}

		for (const auto &triangle : triangles)
		{
			auto intersection = triangle.NearestIntersection(ray);
			if (intersection.has_value())
			{
				return intersection;
			}
		}

		return std::optional<Intersection>();
	}

	Mesh Mesh::LoadObjFile(const std::wstring path)
	{
		return Mesh(ObjFile::Load(path));
	}
}
