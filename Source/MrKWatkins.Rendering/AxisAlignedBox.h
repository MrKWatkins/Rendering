#pragma once
#include "Solid.h"
#include "Point.h"
#include "Triangle.h"

namespace MrKWatkins::Rendering::Geometry
{
	class AxisAlignedBox final : public Solid
	{
		Point minimum;
		Point maximum;

		bool AxisAlignedBox::NearestIntersection(const Ray& ray, double& dNear, double& dFar) const;
	public:
		AxisAlignedBox(const Point& minimum, const Point& maximum);
		AxisAlignedBox(const Point& closestCorner, double width, double height, double depth);

		bool Intersects(const Ray& ray) const override;

		std::unique_ptr<Intersection> NearestIntersection(const Ray& ray) const override;

		const Point& Minimum() const noexcept { return minimum; }
		const Point& Maximum() const noexcept { return maximum; }

		double Width() const noexcept { return abs(maximum.X() - minimum.X()); }
		double Height() const noexcept { return abs(maximum.Y() - minimum.Y()); }
		double Depth() const noexcept { return abs(maximum.Z() - minimum.Z()); }

		/// <summary>
		/// Returns a transformation that would normalize this box, i.e. move it so that the the minimum is at the origin and the maximum has it's largest axis at 1.
		/// </summary>
		Matrix GetNormalizeTransform() const;

		// Factory methods.
		template <typename TContainer>
		static AxisAlignedBox CreateBoundingBoxForPoints(TContainer points)
		{
			if (points.size() == 0)
			{
				throw std::invalid_argument("Container is empty.");
			}

			return CreateBoundingBoxForPoints(std::begin(points), std::end(points));
		}

		template <typename TIterator>
		static AxisAlignedBox CreateBoundingBoxForPoints(TIterator start, TIterator end)
		{
			auto minX = std::numeric_limits<double>::infinity();
			auto minY = std::numeric_limits<double>::infinity();
			auto minZ = std::numeric_limits<double>::infinity();
			auto maxX = -std::numeric_limits<double>::infinity();
			auto maxY = -std::numeric_limits<double>::infinity();
			auto maxZ = -std::numeric_limits<double>::infinity();

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

			if (isinf(minX))
			{
				throw std::invalid_argument("Iterator contained no points.");
			}

			return AxisAlignedBox(Point(minX, minY, minZ), Point(minX, minY, minZ));
		}

		template <typename TContainer>
		static AxisAlignedBox CreateBoundingBoxForTriangles(TContainer triangles)
		{
			if (triangles.size() == 0)
			{
				throw std::invalid_argument("Container is empty.");
			}

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

			if (isinf(minX))
			{
				throw std::invalid_argument("Iterator contained no triangles.");
			}

			return AxisAlignedBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
		}
	};
}
