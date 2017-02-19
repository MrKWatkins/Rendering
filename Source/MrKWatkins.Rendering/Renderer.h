#pragma once
#include "Algorithm.h"
#include "Image.h"
#include <functional>

namespace MrKWatkins::Rendering
{
    enum RendererStatus
    {
        /// <summary>
        /// Rendering is in progress.
        /// </summary>
        InProgress,

        /// <summary>
        /// Rendering has finished.
        /// </summary>
        Finished,

        /// <summary>
        /// <see cref="Renderer::Cancel" /> has been called but the renderer hasn't stopped yet.
        /// </summary>
        Cancelling,

        /// <summary>
        /// <see cref="Renderer::Cancel" /> has been called and rendering has stopped. 
        /// </summary>
        Cancelled
    };

    class Renderer
    {
        Algorithm algorithm;
        std::function<void()> onFinished;
        MutableImage image;

    public:
        Renderer(Algorithm algorithm, int width, int height, std::function<void()> onFinished);

        Renderer(const Renderer& toCopy) = delete;

        /// <summary>
        /// Sends a cancellation to the renderer. Will return immediately but rendering might not stop immediately.
        /// </summary>
        void Cancel();

        /// <summary>
        /// Current progress, 0 = not started, 1 = complete.
        /// </summary>
        double Progress() const;

        RendererStatus Status() const;

        Image TakeSnapshot() const;
    };
}
