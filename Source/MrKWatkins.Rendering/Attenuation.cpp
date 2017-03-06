#include "stdafx.h"
#include "Attenuation.h"

namespace MrKWatkins::Rendering::Lighting
{
    Attenuation::Attenuation(const std::function<double(double)>& function) : function{ function }
    {
    }

    double Attenuation::GetIntensity(double distanceFromLight) const
    {
        return function(distanceFromLight);
    }

    Attenuation Attenuation::None()
    {
        return Attenuation([](double distance)
        {
            return 1.0;
        });
    }

    Attenuation Attenuation::Linear(double halfLightDistance)
    {
        // Half intense at distance d. Therefore 0.5 = kd => k = 0.5/d.
        auto constant = 0.5 / halfLightDistance;
        auto maximumRange = 2 * halfLightDistance;

        return Attenuation([=](double distance)
        {
            if (distance >= maximumRange)
            {
                return 0.0;
            }

            return 1.0 - constant * distance;
        });
    }

    Attenuation Attenuation::Inverse(double halfLightDistance)
    {
        // Half intense at distance d. Therefore 0.5 = k/d => k = 0.5 d.
        auto constant = 0.5 * halfLightDistance;

        return Attenuation([=](double distance)
        {
            if (distance == 0)
            {
                return 1.0;
            }

            return constant / distance;
        });
    }

    Attenuation Attenuation::InverseSquare(double halfLightDistance)
    {
        // Half intense at distance d. Therefore 0.5 = k/d^2 => k = 0.5 d^2.
        auto constant = 0.5 * halfLightDistance * halfLightDistance;

        return Attenuation([=](double distance)
        {
            if (distance == 0)
            {
                return 1.0;
            }

            return constant / (distance * distance);
        });
    }
}
