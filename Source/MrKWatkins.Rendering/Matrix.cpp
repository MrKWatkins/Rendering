#include "stdafx.h"
#include "Matrix.h"
#include "Doubles.h"

namespace MrKWatkins::Rendering::Geometry
{
	Matrix::Matrix()
	{
	}

	Matrix::Matrix(const double elements[16]) : elements { elements[0], elements[1], elements[2], elements[3], elements[4], elements[5], elements[6], elements[7], elements[8], elements[9], elements[10], elements[11], elements[12], elements[13], elements[14], elements[15] }
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
		double elements[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };

		static auto identity = Matrix(elements);

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
