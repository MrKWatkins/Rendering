#include "stdafx.h"
#include "Renderer.h"
#include "Algorithm.h"
#include <mutex>

namespace MrKWatkins::Rendering
{
    class Renderer::Implementation
    {
        std::unique_ptr<Algorithms::Algorithm> algorithm;
        MutableImage image;
        std::mutex lock {};
        RendererStatus status{ InProgress };
        double progress{ 0 };
        std::thread thread;

        void SetPixel(int x, int y, Colour colour)
        {
            std::lock_guard<std::mutex> take(lock);

            image.SetPixel(x, y, colour);

            double totalOperations = image.Width() * image.Height();
            double operationsSoFar = x * image.Height() + y + 1;

            progress = operationsSoFar / totalOperations;
        }

        void RenderingLoop()
        {
            const double width = image.Width();
            const double height = image.Height();

            for (unsigned int x = 0; x < width; x++)
            {
                for (unsigned int y = 0; y < height; y++)
                {
                    auto point = algorithm->RenderPoint(x / width, y / height);

                    SetPixel(x, y, point);

                    if (Status() == Cancelling)
                    {
                        return;
                    }
                }
            }

            std::lock_guard<std::mutex> take(lock);

            status = Finished;
        }

    public:

        Implementation(std::unique_ptr<Algorithms::Algorithm> algorithm, int size) :
            algorithm{ move(algorithm) },
            image{ size, size }
        {
            thread = std::thread(&Implementation::RenderingLoop, this);
        }

        ~Implementation()
        {
            Cancel();

            thread.join();
        }

        void Cancel()
        {
            std::lock_guard<std::mutex> take(lock);

            if (status == InProgress)
            {
                status = Cancelling;
            }
        }

        double Progress()
        {
            std::lock_guard<std::mutex> take(lock);

            return progress;
        }

        RendererStatus Status()
        {
            std::lock_guard<std::mutex> take(lock);

            return status;
        }

        Image TakeSnapshot()
        {
            std::lock_guard<std::mutex> take(lock);

            return Image(image);
        }

        void SnapshotTo(MutableImage& target)
        {
            std::lock_guard<std::mutex> take(lock);

            image.CopyTo(target);
        }
    };

    std::unique_ptr<Renderer> Renderer::StartInternal(std::unique_ptr<Algorithms::Algorithm> algorithm, int size)
    {
        auto implementation = std::make_unique<Implementation>(move(algorithm), size);
        return std::unique_ptr<Renderer>(new Renderer(move(implementation)));
    }

    Renderer::Renderer(std::unique_ptr<Implementation> implementation) :
        implementation{ move(implementation) }
    {
    }

    Renderer::~Renderer()
    {
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    void Renderer::Cancel()
    {
        implementation->Cancel();
    }

    double Renderer::Progress() const
    {
        return implementation->Progress();
    }

    RendererStatus Renderer::Status() const
    {
        return implementation->Status();
    }

    Image Renderer::TakeSnapshot() const
    {
        return implementation->TakeSnapshot();
    }

    void Renderer::SnapshotTo(MutableImage& target) const
    {
        implementation->SnapshotTo(target);
    }
}
