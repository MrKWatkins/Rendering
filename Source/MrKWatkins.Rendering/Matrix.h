#pragma once

namespace MrKWatkins::Rendering::Geometry
{
	class Matrix final
	{
		double elements[16];

		Matrix();
		explicit Matrix(const double elements[16]);
	public:
		Matrix(const Matrix& other);

		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;

		static const Matrix& Zero();
		bool IsZero() const;

		static const Matrix& Identity();
		bool IsIdentity() const;
	};
}

