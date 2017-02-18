#include "stdafx.h"
#include "Renderer.h"
#include <random>

namespace MrKWatkins::Rendering
{
    Renderer::Renderer(int width, int height) : image(width, height)
    {
    }

    void Renderer::Render()
    {
        std::default_random_engine generator { std::random_device{}() };
        std::uniform_real_distribution<double> distribution(0, 1);

        for (unsigned int x = 0; x < image.Width(); x++)
        {
            for (unsigned int y = 0; y < image.Height(); y++)
            {
                image.Pixel(x, y, Colour{ distribution(generator),  distribution(generator),  distribution(generator) });
            }
        }
    }

    const Image& Renderer::Image() const
    {
        return image;
    }
}
