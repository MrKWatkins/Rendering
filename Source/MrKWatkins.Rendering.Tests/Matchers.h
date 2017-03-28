#pragma once
#include "Catch.hpp"
#include "Vector.h"
#include "Point.h"

namespace MrKWatkins::Rendering::Tests
{
	// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor - Catch is at fault here.
    class VectorEquals : public Catch::MatcherBase<Geometry::Vector>
    {
        Geometry::Vector vector;
    public:
		explicit VectorEquals(Geometry::Vector const& vector);

		VectorEquals(VectorEquals const& other);

		bool match(Geometry::Vector const& other) const override;
        
		std::string describe() const override;
    };

    inline VectorEquals Equals(Geometry::Vector const& vector)
    {
        return VectorEquals(vector);
    }

	// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor - Catch is at fault here.
    class PointEquals : public Catch::MatcherBase<Geometry::Point>
    {
        Geometry::Point point;
    public:
		explicit PointEquals(Geometry::Point const& point);

		PointEquals(PointEquals const& other);

		bool match(Geometry::Point const& other) const override;

		std::string describe() const override;
    };

    inline PointEquals Equals(Geometry::Point const& point)
    {
        return PointEquals(point);
    }
}
