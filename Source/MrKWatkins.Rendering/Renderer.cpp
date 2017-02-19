#include "stdafx.h"
#include "Renderer.h"

namespace MrKWatkins::Rendering
{
    template <class TAlgorithm>
    Renderer Renderer::Start(int width, int height, std::function<void()> onFinished)
    {
        return Renderer(std::make_unique(new TAlgorithm), width, height, onFinished);
    }

    Renderer::Renderer(std::unique_ptr<Algorithm> algorithm, int width, int height, std::function<void()> onFinished) : 
        algorithm{move(algorithm)}, 
        image{width, height}, 
        onFinished{onFinished},
        status{ InProgress }
    {
        thread = std::thread(&Renderer::RenderingLoop, this);
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

    void Renderer::RenderingLoop()
    {
    }

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
