#pragma once
#include "stdafx.h"
#include "catch.hpp"
#include "../MrKWatkins.Rendering/Vector.h"

namespace MrKWatkins::Rendering::Tests
{
    struct Equals : Catch::Impl::MatcherImpl<Equals, Geometry::Vector>
    {
    private:
        Geometry::Vector vector;
    public:
        explicit Equals(Geometry::Vector const& vector) : vector{ vector }
        {
        }

        Equals(Equals const& other) : vector{ other.vector }
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
}
