#pragma once

namespace MrKWatkins::Rendering
{
    // TODO: Replace with std::optional after moving to VS2017.
    template <class T>
    class Optional
    {
        T value;
        bool hasValue;

        void VerifyValue() const
        {
            if (!hasValue)
            {
                throw std::logic_error("No value.");
            }
        }

    public:
        Optional() : hasValue{false}
        {
        }

        explicit Optional(const T& value) : value(value), hasValue{true}
        {
        }

        bool HasValue() const
        {
            return hasValue;
        }

        const T& Value() const
        {
            VerifyValue();
            return value;
        }
    };
}
