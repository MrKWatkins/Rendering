#pragma once
#include "Solid.h"
#include "Point.h"
#include "Triangle.h"
#include "RayIntersection.h"

namespace MrKWatkins::Rendering::Geometry
{
	class AxisAlignedBox final : public Solid
	{
		Point minimum;
		Point maximum;

	public:
		AxisAlignedBox(const Point& minimum, const Point& maximum);
		AxisAlignedBox(const Point& closestCorner, double width, double height, double depth);

		const Point& Minimum() const noexcept { return minimum; }
		const Point& Maximum() const noexcept { return maximum; }

		std::optional<RayIntersection> NearestRayIntersection(const Ray& ray) const override;

		Vector GetSurfaceNormal(const RayIntersection& rayIntersection, const Point& pointOnSurface) const override;

		// Factory methods.
		template <typename TContainer>
		static AxisAlignedBox CreateBoundingBoxForPoints(TContainer points)
		{
			return CreateBoundingBoxForPoints(std::begin(points), std::end(points));
		}

		template <typename TIterator>
		static AxisAlignedBox CreateBoundingBoxForPoints(TIterator start, TIterator end)
		{
			double minX, minY, minZ = std::numeric_limits<double>::infinity();
			double maxX, maxY, maxZ = -std::numeric_limits<double>::infinity();

			for (auto iterator = start; iterator != end; ++iterator)
			{
				const Point& point = *iterator;
				minX = std::min(minX, point.X());
				minY = std::min(minY, point.Y());
				minZ = std::min(minZ, point.Z());

				maxX = std::max(maxX, point.X());
				maxY = std::max(maxY, point.Y());
				maxZ = std::max(maxZ, point.Z());
			}

			return AxisAlignedBox(Point(minX, minY, minZ), Point(minX, minY, minZ));
		}

		template <typename TContainer>
		static AxisAlignedBox CreateBoundingBoxForTriangles(TContainer triangles)
		{
			return CreateBoundingBoxForTriangles(std::begin(triangles), std::end(triangles));
		}

		template <typename TIterator>
		static AxisAlignedBox CreateBoundingBoxForTriangles(TIterator start, TIterator end)
		{
			auto minX = std::numeric_limits<double>::infinity();
			auto minY = std::numeric_limits<double>::infinity();
			auto minZ = std::numeric_limits<double>::infinity();
			auto maxX = -std::numeric_limits<double>::infinity();
			auto maxY = -std::numeric_limits<double>::infinity();
			auto maxZ = -std::numeric_limits<double>::infinity();

			for (auto iterator = start; iterator != end; ++iterator)
			{
				const Triangle& triangle = *iterator;

				for (auto& point : triangle)
				{
					minX = std::min(minX, point.X());
					minY = std::min(minY, point.Y());
					minZ = std::min(minZ, point.Z());

					maxX = std::max(maxX, point.X());
					maxY = std::max(maxY, point.Y());
					maxZ = std::max(maxZ, point.Z());
				}
			}

			return AxisAlignedBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
		}
	};
}
