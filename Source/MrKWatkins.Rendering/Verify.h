#pragma once
// Verifications are implemented as macros so we can easily turn them off for super fast code. I tried using functions whose internals were wrapped in an #ifdef but to
// include the parameter name involved (lots) of string allocations which slowed the program down by a factor of two...

#ifdef VERIFY_ENABLED

#define VERIFY_IS_FINITE(parameter) \
if (!std::isfinite(parameter)) \
{ \
	throw std::invalid_argument(#parameter " is not a finite number."); \
}

#define VERIFY_NOT_ZERO(parameter) \
if (parameter == 0)	/* TODO: Should this be a tolerant comparison? */ \
{ \
	throw std::invalid_argument(#parameter " cannot be zero."); \
}

#define VERIFY_ZERO_TO_ONE(parameter) \
if (parameter < 0 || parameter > 1) \
{ \
	throw std::out_of_range(#parameter " equals " + std::to_string(parameter) + " which is not in the range 0 -> 1."); \
}

#define VERIFY_LESS_THAN(maximumExclusive, parameter) \
if (parameter >= maximumExclusive) \
{ \
	throw std::out_of_range(#parameter " is " + std::to_string(parameter) + " which is not less than " + std::to_string(maximumExclusive) + "."); \
}

#define VERIFY_LESS_THAN_OR_EQUAL_TO(maximumInclusive, parameter) \
if (parameter > maximumInclusive) \
{ \
	throw std::out_of_range(#parameter " is " + std::to_string(parameter) + " which is not less than or equal to " + std::to_string(maximumInclusive) + "."); \
}

#define VERIFY_GREATER_THAN(minimumExclusive, parameter) \
if (parameter <= minimumExclusive) \
{ \
	throw std::out_of_range(#parameter " is " + std::to_string(parameter) + " which is not greater than " + std::to_string(minimumExclusive) + "."); \
}

#define VERIFY_GREATER_THAN_OR_EQUAL_TO(minimumInclusive, parameter) \
if (parameter < minimumInclusive) \
{ \
	throw std::out_of_range(#parameter " is " + std::to_string(parameter) + " which is not greater than or equal to " + std::to_string(minimumInclusive) + "."); \
}

#define VERIFY_IS_NORMALIZED(parameter) \
if (!parameter.IsNormalized()) \
{ \
	throw std::invalid_argument(#parameter " is not normalized."); \
}

#else

#define VERIFY_IS_FINITE(parameter)
#define VERIFY_NOT_ZERO(parameter)
#define VERIFY_ZERO_TO_ONE(parameter)
#define VERIFY_LESS_THAN(maximumExclusive, parameter)
#define VERIFY_LESS_THAN_OR_EQUAL_TO(maximumExclusive, parameter)
#define VERIFY_GREATER_THAN(minimumInclusive, parameter)
#define VERIFY_GREATER_THAN_OR_EQUAL_TO(minimumInclusive, parameter)
#define VERIFY_IS_NORMALIZED(parameter)

#endif