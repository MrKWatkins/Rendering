#pragma once
#include "Colour.h"
#include <vector>

namespace MrKWatkins::Rendering
{
    class MutableImage;

    class Image
    {
    protected:
        unsigned int width;
        unsigned int height;
        std::vector<Colour> image;
    public:
        Image(unsigned int width, unsigned int height);
        Image(unsigned int width, unsigned int height, Colour initialColour);

        unsigned int Width() const noexcept { return width; }
        unsigned int Height() const noexcept { return height; }

        Colour GetPixel(unsigned int x, unsigned int y) const;
        void CopyTo(MutableImage& target);
    };

    class MutableImage : public Image
    {
    public:
        MutableImage(unsigned int width, unsigned int height);
        void SetPixel(unsigned int x, unsigned int y, Colour colour);
    };
}
