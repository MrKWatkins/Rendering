#include "stdafx.h"
#include "Matrix.h"
#include "Doubles.h"
#include "Verify.h"

namespace MrKWatkins::Rendering::Geometry
{
	Matrix::Matrix() : elements{}
	{
	}

	Matrix::Matrix(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7, double e8, double e9, double e10, double e11, double e12, double e13, double e14, double e15)
		: elements{ e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15 } 
	{
	}

	Matrix::Matrix(const double elements[16])
		: elements { elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], elements[12], elements[13], elements[14], elements[15] }
	{
	}

	Matrix::Matrix(const Matrix& other) : Matrix(other.elements)
	{
	}

	bool Matrix::operator==(const Matrix& other) const
	{
		for (unsigned int f = 0; f < 16; f++)
		{
			if (!Doubles::AreEqual(elements[f], other.elements[f]))
			{
				return false;
			}
		}
		return true;
	}

	bool Matrix::operator!=(const Matrix& other) const
	{
		for (unsigned int f = 0; f < 16; f++)
		{
			if (!Doubles::AreEqual(elements[f], other.elements[f]))
			{
				return true;
			}
		}
		return false;
	}

	Matrix Matrix::operator+(const Matrix& other) const
	{
		Matrix result;
		for (unsigned int f = 0; f < 16; f++)
		{
			result.elements[f] = elements[f] + other.elements[f];
		}
		return result;
	}

	Matrix Matrix::operator-(const Matrix& other) const
	{
		Matrix result;
		for (unsigned int f = 0; f < 16; f++)
		{
			result.elements[f] = elements[f] - other.elements[f];
		}
		return result;
	}

	Matrix Matrix::operator-() const
	{
		Matrix result;
		for (unsigned int f = 0; f < 16; f++)
		{
			result.elements[f] = -elements[f];
		}
		return result;
	}

	Matrix Matrix::operator*(double scalar) const
	{
		Matrix result;
		for (unsigned int f = 0; f < 16; f++)
		{
			result.elements[f] = elements[f] * scalar;
		}
		return result;
	}

	Matrix operator*(double scalar, const Matrix& matrix)
	{
		return matrix * scalar;
	}

	Matrix Matrix::operator*(const Matrix& other) const
	{
		Matrix result;

		result.elements[0] = elements[0] * other.elements[0] + elements[4] * other.elements[1] + elements[8] * other.elements[2] + elements[12] * other.elements[3];
		result.elements[1] = elements[1] * other.elements[0] + elements[5] * other.elements[1] + elements[9] * other.elements[2] + elements[13] * other.elements[3];
		result.elements[2] = elements[2] * other.elements[0] + elements[6] * other.elements[1] + elements[10] * other.elements[2] + elements[14] * other.elements[3];
		result.elements[3] = elements[3] * other.elements[0] + elements[7] * other.elements[1] + elements[11] * other.elements[2] + elements[15] * other.elements[3];
		result.elements[4] = elements[0] * other.elements[4] + elements[4] * other.elements[5] + elements[8] * other.elements[6]+ elements[12] * other.elements[7];
		result.elements[5] = elements[1] * other.elements[4] + elements[5] * other.elements[5] + elements[9] * other.elements[6]+ elements[13] * other.elements[7];
		result.elements[6] = elements[2] * other.elements[4] + elements[6] * other.elements[5] + elements[10] * other.elements[6]+ elements[14] * other.elements[7];
		result.elements[7] = elements[3] * other.elements[4] + elements[7] * other.elements[5] + elements[11] * other.elements[6]+ elements[15] * other.elements[7];
		result.elements[8] = elements[0] * other.elements[8] + elements[4] * other.elements[9] + elements[8] * other.elements[10]+ elements[12] * other.elements[11];
		result.elements[9] = elements[1] * other.elements[8] + elements[5] * other.elements[9] + elements[9] * other.elements[10]+ elements[13] * other.elements[11];
		result.elements[10] = elements[2] * other.elements[8] + elements[6] * other.elements[9] + elements[10] * other.elements[10]+ elements[14] * other.elements[11];
		result.elements[11] = elements[3] * other.elements[8] + elements[7] * other.elements[9] + elements[11] * other.elements[10]+ elements[15] * other.elements[11];
		result.elements[12] = elements[0] * other.elements[12] + elements[4] * other.elements[13] + elements[8] * other.elements[14]+ elements[12] * other.elements[15];
		result.elements[13] = elements[1] * other.elements[12] + elements[5] * other.elements[13] + elements[9] * other.elements[14]+ elements[13] * other.elements[15];
		result.elements[14] = elements[2] * other.elements[12] + elements[6] * other.elements[13] + elements[10] * other.elements[14]+ elements[14] * other.elements[15];
		result.elements[15] = elements[3] * other.elements[12] + elements[7] * other.elements[13] + elements[11] * other.elements[14]+ elements[15] * other.elements[15];

		return result;
	}

	Point Matrix::Transform(const Point& point) const
	{
		// If we're transforming a point multiply a homongenous 4-vector of the form (x, y, z, 1).
		return Point(
			elements[0] * point.X() + elements[4] * point.Y() + elements[8] * point.Z() + elements[12],
			elements[1] * point.X() + elements[5] * point.Y() + elements[9] * point.Z() + elements[13],
			elements[2] * point.X() + elements[6] * point.Y() + elements[10] * point.Z() + elements[14]);
	}

	Vector Matrix::Transform(const Vector& vector) const
	{
		// If we're transforming a vector multiply a homongenous 4-vector of the form (x, y, z, 0) - effectively removes the translation component.
		return Vector(
			elements[0] * vector.X() + elements[4] * vector.Y() + elements[8] * vector.Z(),
			elements[1] * vector.X() + elements[5] * vector.Y() + elements[9] * vector.Z(),
			elements[2] * vector.X() + elements[6] * vector.Y() + elements[10] * vector.Z());
	}

	double Matrix::operator()(unsigned int i, unsigned int j) const
	{
		return elements[i + 4 * j];
	}

	Matrix Matrix::Scale(double factor)
	{
		return Scale(factor, factor, factor);
	}

	Matrix Matrix::ScaleX(double factor)
	{
		return Scale(factor, 1.0, 1.0);
	}

	Matrix Matrix::ScaleY(double factor)
	{
		return Scale(1.0, factor, 1.0);
	}

	Matrix Matrix::ScaleZ(double factor)
	{
		return Scale(1.0, 1.0, factor);
	}

	Matrix Matrix::Scale(double xFactor, double yFactor, double zFactor)
	{
		VERIFY_NOT_NEGATIVE(xFactor);
		VERIFY_NOT_NEGATIVE(yFactor);
		VERIFY_NOT_NEGATIVE(zFactor);

		Matrix scale;
		scale.elements[0] = xFactor;
		scale.elements[5] = yFactor;
		scale.elements[10] = zFactor;
		return scale;
	}

	Matrix Matrix::Translate(const Vector& vector)
	{
		return Translate(vector.X(), vector.Y(), vector.Z());
	}

	Matrix Matrix::TranslateX(double distance)
	{
		return Translate(distance, 0.0, 0.0);
	}

	Matrix Matrix::TranslateY(double distance)
	{
		return Translate(0.0, distance, 0.0);
	}

	Matrix Matrix::TranslateZ(double distance)
	{
		return Translate(0.0, 0.0, distance);
	}

	Matrix Matrix::Translate(double xDistance, double yDistance, double zDistance)
	{
		Matrix translation;
		translation.elements[0] = 1.0;
		translation.elements[5] = 1.0;
		translation.elements[10] = 1.0;
		translation.elements[12] = xDistance;
		translation.elements[13] = yDistance;
		translation.elements[14] = zDistance;
		translation.elements[15] = 1.0;
		return translation;
	}

	const Matrix& Matrix::Zero()
	{
		static auto zero = Matrix();

		return zero;
	}

	bool Matrix::IsZero() const
	{
		for (unsigned int f = 0; f < 16; f++)
		{
			if (!Doubles::IsZero(elements[f]))
			{
				return false;
			}
		}
		return true;
	}

	const Matrix& Matrix::Identity()
	{
		static auto identity = Matrix(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		return identity;
	}

	bool Matrix::IsIdentity() const
	{
		return Doubles::IsOne(elements[0]) && Doubles::IsZero(elements[1]) && Doubles::IsZero(elements[2]) && Doubles::IsZero(elements[3]) &&
			Doubles::IsZero(elements[4]) && Doubles::IsOne(elements[5]) && Doubles::IsZero(elements[6]) && Doubles::IsZero(elements[7]) &&
			Doubles::IsZero(elements[8]) && Doubles::IsZero(elements[9]) && Doubles::IsOne(elements[10]) && Doubles::IsZero(elements[11]) &&
			Doubles::IsZero(elements[12]) && Doubles::IsZero(elements[13]) && Doubles::IsZero(elements[14]) && Doubles::IsOne(elements[15]);
	}
}
