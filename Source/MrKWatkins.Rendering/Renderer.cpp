#include "stdafx.h"
#include "Renderer.h"

namespace MrKWatkins::Rendering
{
    Renderer::Renderer(Algorithm algorithm, int width, int height, std::function<void()> onFinished) : image(width, height)
    {
    }

    void Renderer::Cancel()
    {
    }

    double Renderer::Progress() const
    {
    }

    RendererStatus Renderer::Status() const
    {
    }

    Image Renderer::TakeSnapshot() const
    {
    }

    // Render loop:

    /*
    for (unsigned int x = 0; x < image.Width(); x++)
    {
        for (unsigned int y = 0; y < image.Height(); y++)
        {
            image.Pixel(x, y, algorithm.RenderPoint(<convert coords to 0, 1>));
        }
    }
    */
}
