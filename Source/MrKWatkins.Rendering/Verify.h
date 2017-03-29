#pragma once

namespace MrKWatkins::Rendering::Verify
{
	template<typename T>
	void ZeroToOne(T value, const std::string& parameterName)
	{
		static_assert(std::is_arithmetic<T>::value, "T is not an arithmetic type.");

		if (value < 0 || value > 1)
		{
			throw std::out_of_range("Value of " + parameterName + " is " + std::to_string(value) + " which is not in the range 0 -> 1.");
		}
	}

	template<typename T>
	void LessThan(const T maximumExclusive, const T value, const std::string& parameterName)
	{
		static_assert(std::is_arithmetic<T>::value, "T is not an arithmetic type.");

		if (value >= maximumExclusive)
		{
			throw std::out_of_range("Value of " + parameterName + " is " + std::to_string(value) + " which is not less than " + std::to_string(maximumExclusive) + ".");
		}
	}

	template<typename T>
	void LessThanOrEqualTo(const T maximumInclusive, const T value, const std::string& parameterName)
	{
		// As we're doing equality here only allow integral types to avoid floating point errors.
		static_assert(std::is_integral<T>::value, "T is not an integral type.");

		if (value > maximumInclusive)
		{
			throw std::out_of_range("Value of " + parameterName + " is " + std::to_string(value) + " which is not less than or equal to " + std::to_string(maximumInclusive) + ".");
		}
	}

	template<typename T>
	void GreaterThan(const T minimumExclusive, const T value, const std::string& parameterName)
	{
		static_assert(std::is_arithmetic<T>::value, "T is not an arithmetic type.");

		if (value <= minimumExclusive)
		{
			throw std::out_of_range("Value of " + parameterName + " is " + std::to_string(value) + " which is not greater than " + std::to_string(minimumExclusive) + ".");
		}
	}

	template<typename T>
	void GreaterThanOrEqualTo(const T minimumInclusive, const T value, const std::string& parameterName)
	{
		// As we're doing equality here only allow integral types to avoid floating point errors.
		static_assert(std::is_integral<T>::value, "T is not an integral type.");

		if (value < minimumInclusive)
		{
			throw std::out_of_range("Value of " + parameterName + " is " + std::to_string(value) + " which is not greater than or equal to " + std::to_string(minimumInclusive) + ".");
		}
	}
}