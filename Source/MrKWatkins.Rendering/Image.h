#pragma once
#include "Colour.h"
#include <vector>

namespace MrKWatkins::Rendering
{
    class Image
    {
    protected:
        unsigned int width;
        unsigned int height;
        std::vector<std::vector<Colour>> image;
    public:
        Image(unsigned int width, unsigned int height);
        Image(const Image& that) = delete;

        unsigned int Width() const noexcept { return width; }
        unsigned int Height() const noexcept { return height; }

        Colour Pixel(unsigned int x, unsigned int y) const;
    };

    class MutableImage : public Image
    {
    public:
        MutableImage(unsigned width, unsigned height);
        void Pixel(unsigned int x, unsigned int y, Colour colour);
    };
}
