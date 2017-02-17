#include "stdafx.h"
#include "PlaceHelper.h"

namespace MrKWatkins::Rendering::UI::PlaceHelper
{
    std::string EncloseWithPadding(const std::string div, const int paddingPixels)
    {
        // To give padding we:
        // 1. Put a section either side with the padding to give the horizontal padding.
        // 2. Enclose that in a section.
        // 3. Put a section either side of that with the padding.
        // 4. Give the outer sections vertical layout.

        auto padding = "<weight=" + std::to_string(paddingPixels) + ">";
        auto horizontal = "<" + padding + "<" + div + ">" + padding + ">";
        return "vert " + padding + horizontal + padding;
    }
}