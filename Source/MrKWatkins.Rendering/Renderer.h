#pragma once
#include "Image.h"
#include "Algorithm.h"

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

    class Renderer final
    {
		// TODO: Don't use PIMPL.
        class Implementation;
        std::unique_ptr<Implementation> implementation;

	    explicit Renderer(std::unique_ptr<Implementation> implementation);

        static std::unique_ptr<Renderer> StartInternal(std::unique_ptr<Algorithms::Algorithm> algorithm, int size);

    public:
        template<typename TAlgorithm, class... TConstructorArguments>
        static std::unique_ptr<Renderer> Start(int size, TConstructorArguments&&... constructorArguments)
        {
            static_assert(std::is_base_of<Algorithms::Algorithm, TAlgorithm>::value, "TAlgorithm is not an instance of Algorithm.");

            auto algorithm = std::unique_ptr<Algorithms::Algorithm>(new TAlgorithm(std::forward<TConstructorArguments>(constructorArguments)...));
            return StartInternal(move(algorithm), size);
        }

        Renderer(const Renderer& toCopy) = delete;
        ~Renderer();

        /// <summary>
        /// Sends a cancellation to the renderer. Will return immediately but rendering might not stop immediately.
        /// </summary>
        void Cancel();
        
        /// <summary>
        /// Current progress, 0 = not started, 1 = complete.
        /// </summary>
        double Progress() const;

        RendererStatus Status() const;

		std::string Error() const;

        Image TakeSnapshot() const;
        
        void SnapshotTo(MutableImage& target) const;
    };
}
