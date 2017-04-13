#pragma once

namespace MrKWatkins::Rendering::Geometry
{
	class Solid;

	/// <summary>
	/// Details of an intersection in terms of the ray, i.e. d, the distance from the origin along the ray's direction and whether the ray's origin
	/// is inside the solid or not.
	/// </summary>
	class RayIntersection final
	{
		double d; 
		bool intersectingOutside; 
		double u; 
		double v; 
		const Solid* childSolid;

		RayIntersection(double d, bool intersectingOutside, double u, double v, const Solid* childSolid);
	public:
		RayIntersection(double d, bool intersectingOutside);
		RayIntersection(double d, bool intersectingOutside, double u, double v);
		RayIntersection(const RayIntersection& childIntersection, const Solid* childSolid);

		/// <summary>
		/// The distance along the ray to the intersection point.
		/// </summary>
		double D() const noexcept { return d; }

		/// <summary>
		/// Whether the ray is intersecting the outside of the solid or not. For a 2D solid (e.g. plane, triangle) 'outside' means the 'front'.
		/// </summary>
		bool IntersectingOutside() const noexcept { return intersectingOutside; }

		/// <summary>
		/// Barycentric u co-ordinate of the intersection point, if supported by the solid being intersected.
		/// </summary>
		double U() const noexcept { return u; }

		/// <summary>
		/// Barycentric v co-ordinate of the intersection point, if supported by the solid being intersected.
		/// </summary>
		double V() const noexcept { return v; }

		/// <summary>
		/// Barycentric w co-ordinate of the intersection point, if supported by the solid being intersected.
		/// </summary>
		double W() const noexcept { return 1 - u - v; }

		/// <summary>
		/// If the solid is a composite (e.g. a mesh) then this contains the child solid that was intersected with.
		/// </summary>
		const Solid* ChildSolid() const noexcept { return childSolid; }
	};
}
