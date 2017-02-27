#pragma once
#include <string>

namespace MrKWatkins::Rendering::Geometry
{
    /// <summary>
    /// An immutable three-dimensional vector.
    /// </summary>
    struct Vector
    {
    private:
        double x;
        double y;
        double z;
    public:
        Vector(double x, double y, double z);

        double X() const noexcept { return x; }
        double Y() const noexcept { return y; }
        double Z() const noexcept { return z; }

        double Length() const;

        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        Vector operator-() const;

        Vector operator*(double scalar) const;
        friend Vector operator*(double scalar, const Vector& vector);
        Vector operator/(double scalar) const;

        double Dot(const Vector& other) const;
        Vector Cross(const Vector& other) const;
        Vector Normalize() const;

        std::string ToString() const;
        friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

        static Vector Zero() noexcept { return Vector(0.0, 0.0, 0.0); }
    };
}
