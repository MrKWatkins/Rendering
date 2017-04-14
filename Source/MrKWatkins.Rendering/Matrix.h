#pragma once
#include "Point.h"

namespace MrKWatkins::Rendering::Geometry
{
	class Triangle;

	class Matrix final
	{
		double elements[16];

		Matrix();
		explicit Matrix(const double elements[16]);
		Matrix(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7, double e8, double e9, double e10, double e11, double e12, double e13, double e14, double e15);
	public:
		Matrix(const Matrix& other);

		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;

		Matrix operator+(const Matrix& other) const;
		Matrix operator-(const Matrix& other) const;
		Matrix operator-() const;

		Matrix operator*(double scalar) const;
		friend Matrix operator*(double scalar, const Matrix& matrix);
		Matrix operator*(const Matrix& other) const;

		Point Transform(const Point& point) const;
		Vector Transform(const Vector& vector) const;

		double operator()(unsigned int i, unsigned int j) const;

		static Matrix Scale(double factor);
		static Matrix ScaleX(double factor);
		static Matrix ScaleY(double factor);
		static Matrix ScaleZ(double factor);
		static Matrix Scale(double xFactor, double yFactor, double zFactor);

		static Matrix Translate(const Vector& vector);
		static Matrix TranslateX(double distance);
		static Matrix TranslateY(double distance);
		static Matrix TranslateZ(double distance);
		static Matrix Translate(double xDistance, double yDistance, double zDistance);

		// TODO: Be nice to have some type for angles with easy conversion to/from degrees/radians.
		static Matrix RotateX(double radians);
		static Matrix RotateY(double radians);
		static Matrix RotateZ(double radians);

		static const Matrix& Zero();
		bool IsZero() const;

		static const Matrix& Identity();
		bool IsIdentity() const;
	};
}

