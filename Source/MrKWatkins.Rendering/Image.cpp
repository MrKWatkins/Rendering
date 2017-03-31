#include "stdafx.h"
#include "Image.h"
#include "Verify.h"

namespace MrKWatkins::Rendering
{
    Image::Image(unsigned int width, unsigned int height) : Image(width, height, Colour::Black())
    {
    }

	Image::Image(unsigned int width, unsigned int height, const Colour& initialColour) : width{ width }, height{ height }, image{ width * height, initialColour }
	{
	}

	const Colour& Image::GetPixel(unsigned int x, unsigned int y) const
    {
		// We could use at() to verify but we want a better error message.
		Verify::LessThan(width, x, "x");
		Verify::LessThan(height, y, "y");

        return image[x + y * height];
    }

    void Image::CopyTo(MutableImage& target)
    {
        width = target.Width();
        height = target.Height();
        target.image.assign(image.begin(), image.end());
    }

    MutableImage::MutableImage(unsigned int width, unsigned int height) : Image(width, height)
    {
    }

	void MutableImage::SetPixel(unsigned int x, unsigned int y, const Colour& colour)
	{
		// We could use at() to verify but we want a better error message.
		Verify::LessThan(width, x, "x");
		Verify::LessThan(height, y, "y");

        image[x + y * height] = colour;
    }
}
