#pragma once
#include "Colour.h"

namespace MrKWatkins::Rendering::Algorithms
{
    class Algorithm
    {
    public:
        Algorithm() = default;
        virtual ~Algorithm() = default;

        /// <summary>
        /// Render the point between 0, 0 and 1, 1.
        /// </summary>
        // TODO: Worry about a view window, camera position, aspect ratio etc.
        virtual Colour RenderPoint(double x, double y) = 0;
    };
}
