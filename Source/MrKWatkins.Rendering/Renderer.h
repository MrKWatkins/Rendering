#pragma once
#include "Image.h"

namespace MrKWatkins::Rendering
{
    class Renderer
    {
        MutableImage image;
    public:
        Renderer(int width, int height);

        void Render();

        const Image& Image() const;
    };
}
