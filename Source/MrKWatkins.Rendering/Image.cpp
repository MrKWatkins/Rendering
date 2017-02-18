#include "stdafx.h"
#include "Image.h"

namespace MrKWatkins::Rendering
{
    Image::Image(unsigned int width, unsigned int height) : width{ width }, height{ height }
    {
        image.reserve(width);
        for (unsigned int f = 0; f < width; f++)
        {
            image.push_back(std::vector<Colour>{ height });
        }
    }

    Colour Image::Pixel(unsigned int x, unsigned int y) const
    {
        // TODO: Parameter validation. Could use at() of course but we want a better error message.
        return image[x][y];
    }

    MutableImage::MutableImage(unsigned width, unsigned height) : Image(width, height)
    {
    }

    void MutableImage::Pixel(unsigned x, unsigned y, Colour colour)
    {
        // TODO: Parameter validation. Could use at() of course but we want a better error message.
        image[x][y] = colour;
    }
}
