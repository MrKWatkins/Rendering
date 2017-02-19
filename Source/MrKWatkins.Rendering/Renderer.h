#pragma once
#include "Algorithm.h"
#include "Image.h"
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

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
        Cancelled,

        /// <summary>
        /// An exception occurred whilst rendering.
        /// </summary>
        Error
    };

    class Renderer
    {
        std::unique_ptr<Algorithm> algorithm;
        MutableImage image;
        std::function<void()> onFinished;
        std::mutex lock;
        RendererStatus status;
        std::thread thread;

        Renderer(std::unique_ptr<Algorithm> algorithm, int width, int height, std::function<void()> onFinished);

        void RenderingLoop();

    public:
        template<class TAlgorithm> 
        static Renderer Start(int width, int height, std::function<void()> onFinished);

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
