#include "stdafx.h"
#include "Image.h"

namespace MrKWatkins::Rendering
{
    Image::Image(unsigned int width, unsigned int height) : Image(width, height, Colour { 0, 0, 0 })
    {
    }

    Image::Image(unsigned int width, unsigned int height, Colour initialColour) : width{ width }, height{ height }, image{width * height, initialColour}
    {
    }

    Colour Image::GetPixel(unsigned int x, unsigned int y) const
    {
        // TODO: Parameter validation. Could use at() of course but we want a better error message.
        return image[x + y * height];
    }

    void Image::CopyTo(MutableImage& target)
    {
        width = target.Width();
        height = target.Height();
        target.image.assign(image.begin(), image.end());
    }

    MutableImage::MutableImage(unsigned width, unsigned height) : Image(width, height)
    {
    }

    void MutableImage::SetPixel(unsigned x, unsigned y, Colour colour)
    {
        // TODO: Parameter validation. Could use at() of course but we want a better error message.
        image[x + y * height] = colour;
    }
}
