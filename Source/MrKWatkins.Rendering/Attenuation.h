#pragma once
#include <functional>

namespace MrKWatkins::Rendering::Lighting
{
    class Attenuation final
    {
        std::function<double(double)> function;
        explicit Attenuation(const std::function<double(double)>& function);
    public:
        double GetIntensity(double distanceFromLight) const;

        static Attenuation None();
        static Attenuation Linear(double halfLightDistance);
        static Attenuation Inverse(double halfLightDistance);
        static Attenuation InverseSquare(double halfLightDistance);
    };
}
