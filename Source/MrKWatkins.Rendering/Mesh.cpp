#include "stdafx.h"
#include "Mesh.h"
#include "Verify.h"
#include "Matrix.h"

namespace MrKWatkins::Rendering::Geometry
{
	Mesh::Mesh(const std::vector<Triangle>& triangles) : triangles{ triangles }, boundingBox{ AxisAlignedBox::CreateBoundingBoxForTriangles(triangles) }
	{
	}

	Mesh::Mesh(const IO::ObjFile& objFile) : Mesh(objFile.ToTriangles())
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

	Mesh Mesh::LoadObjFile(const std::wstring path)
	{
		return Mesh(IO::ObjFile::Load(path));
	}

	class MeshIntersection final : public Intersection
	{
		std::unique_ptr<Intersection> triangleIntersection;

	protected:
		Vector CalculateNormal() const override
		{
			return triangleIntersection->Normal();
		}
	public:
		explicit MeshIntersection(std::unique_ptr<Intersection> triangleIntersection)
			: Intersection(triangleIntersection->Ray(), triangleIntersection->DistanceAlongRay()), triangleIntersection { move(triangleIntersection) }
		{
		}
	};

	std::unique_ptr<Intersection> Mesh::NearestIntersection(const Ray& ray) const
	{
		if (!boundingBox.Intersects(ray))
		{
			return nullptr;
		}

		std::unique_ptr<MeshIntersection> nearestIntersection = nullptr;
		for (auto& triangle : triangles)
		{
			auto intersection = triangle.NearestIntersection(ray);
			if (intersection != nullptr &&
				(nearestIntersection == nullptr || intersection->DistanceAlongRay() < nearestIntersection->DistanceAlongRay()))
			{
				nearestIntersection.reset(new MeshIntersection(move(intersection)));
			}
		}

		return nearestIntersection;
	}
}
