#include "stdafx.h"
#include "Light.h"

namespace MrKWatkins::Rendering::Lighting
{
    Light::Light(const Rendering::Colour& colour, const Attenuation& attenuation) : colour{ colour }, attenuation { attenuation }
    {
    }
}
