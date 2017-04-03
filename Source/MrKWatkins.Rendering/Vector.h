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
        double x;
        double y;
        double z;
		bool isNormalized;
		Vector(double x, double y, double z, bool isNormalized);
    public:
		Vector(double x, double y, double z);
        explicit Vector(const Point& point);

        double X() const noexcept { return x; }
        double Y() const noexcept { return y; }
        double Z() const noexcept { return z; }

        double Length() const;
		double LengthSquared() const;

		/// <summary>
		/// Is this vector normalized, i.e. has it been created with the Normalize() method? A vector could be normalized without calling this of course however
		/// we do not test for this on construction because it's an expensive check.
		/// </summary>
		bool IsNormalized() const noexcept { return isNormalized; }

        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        Vector operator-() const;

        Vector operator*(double scalar) const;
        friend Vector operator*(double scalar, const Vector& vector);
        Vector operator/(double scalar) const;

		double operator [](unsigned int index) const;

        double Dot(const Vector& other) const;
        Vector Cross(const Vector& other) const;
        Vector Normalize() const;

		Vector ReflectAbout(const Vector& normal) const;

        std::string ToString() const;
        friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

		static const Vector& Zero() noexcept;
		static const Vector& I() noexcept;
		static const Vector& J() noexcept;
		static const Vector& K() noexcept;
		static const Vector& Axis(unsigned int index);
    };
}
