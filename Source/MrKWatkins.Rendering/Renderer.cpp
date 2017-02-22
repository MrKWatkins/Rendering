#include "stdafx.h"
#include "Renderer.h"
#include "Algorithm.h"
#include <mutex>
#include "RandomAlgorithm.h"

namespace MrKWatkins::Rendering
{
    class Renderer::Implementation
    {
        std::unique_ptr<RandomAlgorithm> algorithm;
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
            double operationsSoFar = x * image.Height() + y;

            progress = operationsSoFar / totalOperations;
        }

        void RenderingLoop()
        {
            for (unsigned int x = 0; x < image.Width(); x++)
            {
                for (unsigned int y = 0; y < image.Height(); y++)
                {
                    auto point = algorithm->RenderPoint(x == 0 ? 0 : 1 / x, y == 0 ? 0 : 1 / y);

                    SetPixel(x, y, point);
                    //std::this_thread::sleep_for(std::chrono::microseconds(10));
                }
            }
        }

    public:

        Implementation(std::unique_ptr<RandomAlgorithm> algorithm, int size) :
            algorithm{ move(algorithm) },
            image{ size, size }
        {
            thread = std::thread(&Implementation::RenderingLoop, this);
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

    //template <typename TAlgorithm>
    std::unique_ptr<Renderer> Renderer::Start(int size)
    {
        auto algorithm = std::unique_ptr<RandomAlgorithm>(new RandomAlgorithm());
        auto implementation = std::unique_ptr<Implementation>(new Implementation(std::move(algorithm), size));
        return std::unique_ptr<Renderer>(new Renderer(std::move(implementation)));
    }

    Renderer::Renderer(std::unique_ptr<Implementation> implementation) :
        implementation{ move(implementation) }
    {
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Cancel()
    {
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
