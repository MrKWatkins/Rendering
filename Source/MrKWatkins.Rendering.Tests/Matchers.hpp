#pragma once
#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"
#include "../MrKWatkins.Rendering/Point.h"

namespace MrKWatkins::Rendering::Tests
{
    struct VectorEquals : Catch::Impl::MatcherImpl<VectorEquals, Geometry::Vector>
    {
    private:
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

        std::string toString() const override
        {
            return "equals " + vector.ToString();
        }
    };

    struct PointEquals : Catch::Impl::MatcherImpl<PointEquals, Geometry::Point>
    {
    private:
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

        std::string toString() const override
        {
            return "equals " + point.ToString();
        }
    };
}
