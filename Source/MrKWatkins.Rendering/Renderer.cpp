#include "stdafx.h"
#include "Renderer.h"
#include "Algorithm.h"
#include <mutex>

using namespace std::chrono;

namespace MrKWatkins::Rendering
{
	const int BlockSize = 16;

	// TODO: Don't use PIMPL and tidy this up.
    class Renderer::Implementation
    {
        std::unique_ptr<Algorithms::Algorithm> algorithm;
        MutableImage image;
        std::mutex lock {};
        RendererStatus status{ InProgress };
		std::string statusMessage{ "" };
		unsigned int nextBlock{ 0 };
		unsigned int totalBlocks;
        std::vector<std::thread> threads;
		unsigned int threadsInProgress;

		high_resolution_clock clock;
		steady_clock::time_point startTime = clock.now();

		void SetError(const std::exception& exception)
		{
			if (Status() != Error)
			{
				std::lock_guard<std::mutex> take(lock);

				status = Error;
				statusMessage = exception.what();
			}
		}

		int DecrementThreadsInProgress()
		{
			std::lock_guard<std::mutex> take(lock);
			threadsInProgress--;
			return threadsInProgress;
		}

		std::optional<unsigned int> TakeBlock()
		{
			std::lock_guard<std::mutex> take(lock);
			auto block = nextBlock;
			if (block < totalBlocks)
			{
				nextBlock++;
				return block;
			}
			return std::optional<unsigned int>();
		}

		void SetBlock(unsigned int xStart, unsigned int yStart, const Colour* block)
        {
            std::lock_guard<std::mutex> take(lock);

			for (unsigned int x = 0; x < BlockSize; x++)
			{
				for (unsigned int y = 0; y < BlockSize; y++)
				{
					image.SetPixel(xStart + x, yStart + y, block[x + y * BlockSize]);
				}
			}
        }

		void RenderBlock(unsigned int blockNumber)
        {
			auto blocksInWidth = image.Width() / BlockSize;
	        auto xStart = BlockSize * (blockNumber % blocksInWidth);
	        auto yStart = BlockSize * (blockNumber / blocksInWidth);
			double width = image.Width();
			double height = image.Height();
			Colour block[BlockSize * BlockSize];
			for (unsigned int x = 0; x < BlockSize; x++)
			{
				for (unsigned int y = 0; y < BlockSize; y++)
				{
					block[x + y * BlockSize] = algorithm->RenderPoint((x + xStart) / width, 1 - (y + yStart) / height);

					if (Status() != InProgress)
					{
						return;
					}
				}
			}
			
			SetBlock(xStart, yStart, block);
        }

        void RenderingLoop()
        {
			auto block = TakeBlock();
			while (block.has_value())
			{
				try
				{
					RenderBlock(block.value());
				}
				catch (const std::exception& exception)
				{
					SetError(exception);

					return;
				}

				if (Status() != InProgress)
				{
					break;
				}

				block = TakeBlock();
			}

			auto inProgress = DecrementThreadsInProgress();

			std::lock_guard<std::mutex> take(lock);
			if (inProgress == 0)
			{
				auto endTime = clock.now();

				// convert from the clock rate to a millisecond clock
				auto seconds = duration_cast<milliseconds>(endTime - startTime);

				status = Finished;
				statusMessage = "Time taken: " + std::to_string(seconds.count() / 1000.0) + "s";
			}
        }

    public:

        Implementation(std::unique_ptr<Algorithms::Algorithm> algorithm, int size) : algorithm{ move(algorithm) }, image{ size, size }
        {
			if (image.Width() % BlockSize != 0)
			{
				throw std::logic_error("Image width (" + std::to_string(image.Width()) + ") must be a multiple of the block size. (" + std::to_string(BlockSize) + ")");
			}
			if (image.Height() % BlockSize != 0)
			{
				throw std::logic_error("Image height (" + std::to_string(image.Height()) + ") must be a multiple of the block size " + std::to_string(BlockSize) + ".");
			}

			totalBlocks = (image.Width() / BlockSize) * (image.Height() / BlockSize);

			auto concurrentThreadsSupported = std::thread::hardware_concurrency();
			auto threadsToCreate = std::max(1U, concurrentThreadsSupported - 1);		// Leave a thread spare for the UI.
			threadsInProgress = threadsToCreate;

			std::lock_guard<std::mutex> take(lock);
			for (auto thread = 0U; thread < threadsToCreate; thread++)
			{
				threads.push_back(std::thread(&Implementation::RenderingLoop, this));
			}
        }

        ~Implementation()
        {
            Cancel();

			for (auto& thread : threads)
			{
				thread.join();
			}
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

            return static_cast<double>(std::max(0U, nextBlock - threadsInProgress)) / totalBlocks;;
        }

        std::string StatusMessage()
        {
            std::lock_guard<std::mutex> take(lock);

            return statusMessage;
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

	std::string Renderer::StatusMessage() const
	{
		return implementation->StatusMessage();
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
