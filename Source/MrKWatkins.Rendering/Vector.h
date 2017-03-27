#pragma once

namespace MrKWatkins::Rendering::Geometry
{
    // Need a forward declaration of Point to avoid circular references between Point and Vector.
    class Point;

    /// <summary>
    /// An immutable three-dimensional vector.
    /// </summary>
    class Vector final
    {
        static Vector zero;
        static Vector i;
        static Vector j;
        static Vector k;

        double x;
        double y;
        double z;
    public:
        explicit Vector(const Point& point);
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

        static const Vector& Zero() noexcept { return zero; }
        static const Vector& I() noexcept { return i; }
        static const Vector& J() noexcept { return j; }
        static const Vector& K() noexcept { return k; }
    };
}
