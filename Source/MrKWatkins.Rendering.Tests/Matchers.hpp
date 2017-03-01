#pragma once
#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"
#include "../MrKWatkins.Rendering/Point.h"

// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor - Catch is at fault here.
namespace MrKWatkins::Rendering::Tests
{
    class VectorEquals : public Catch::MatcherBase<Geometry::Vector>
    {
        Geometry::Vector vector;
    public:
        explicit VectorEquals(Geometry::Vector const& vector) : vector{ vector }
        {
        }

        VectorEquals(VectorEquals const& other) : vector{ other.vector }
        {
        }

        bool match(Geometry::Vector const& other) const override
        {
            return vector.X() == Approx(other.X()) &&
                vector.Y() == Approx(other.Y()) &&
                vector.Z() == Approx(other.Z());
        }
        
        std::string describe() const override
        {
            return "equals " + vector.ToString();
        }
    };

    inline VectorEquals Equals(Geometry::Vector const& vector)
    {
        return VectorEquals(vector);
    }

    class PointEquals : public Catch::MatcherBase<Geometry::Point>
    {
        Geometry::Point point;
    public:
        explicit PointEquals(Geometry::Point const& point) : point{ point }
        {
        }

        PointEquals(PointEquals const& other) : point{ other.point }
        {
        }

        bool match(Geometry::Point const& other) const override
        {
            return point.X() == Approx(other.X()) &&
                point.Y() == Approx(other.Y()) &&
                point.Z() == Approx(other.Z());
        }

        std::string describe() const override
        {
            return "equals " + point.ToString();
        }
    };

    inline PointEquals Equals(Geometry::Point const& point)
    {
        return PointEquals(point);
    }
}
// ReSharper restore CppPolymorphicClassWithNonVirtualPublicDestructor
