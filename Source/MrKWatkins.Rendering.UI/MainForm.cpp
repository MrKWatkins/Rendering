#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/detail/inner_fwd_implement.hpp>
#include "../MrKWatkins.Rendering/Random.h"
#include "../MrKWatkins.Rendering/Gradient.h"

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    void MainForm::Layout() const
    {
        place layout{ *this };
        layout.div("margin=10 gap=10 vert<weight=35 <margin=[5,0,0,0] progressText><weight=100 margin=[0,0,10,10] cancel>><view>");
        layout["progressText"] << progressText;
        layout["view"] << view;
        layout["cancel"] << cancel;
        layout.collocate();
    }

    std::string MainForm::BuildProgressMessage(double progress)
    {
        return "Progress: " + std::to_string(progress * 100) + "%";
    }

    MainForm::MainForm() : form(API::make_center(720, 755), appear::decorate<appear::taskbar>()), imageBuffer { 700, 700 }
    {
        graphicsBuffer = { nana::size{ 700, 700 } };
        graphicsBuffer.make(nana::size{ 700, 700 });

        renderer = Renderer::Start<Algorithms::Gradient>(700);

        caption("Rendering");
        progressText.caption(BuildProgressMessage(0));
        cancel.caption("Cancel");

        cancel.events().click([&]
        {
            renderer->Cancel();
        });


        view.bgcolor(colors::black);
        viewDrawing.draw_diehard([&](graphics& graphics)
        {
            graphicsBuffer.stretch(graphics, rectangle(graphics.size()));
        });

        Layout();

        updateTimer.interval(1000);
        updateTimer.elapse([&]()
        {
            auto status = renderer->Status();
            if (status != InProgress)
            {
                // Disable cancel if we're no longer in progress.
                cancel.enabled(false);

                // If we're not still in the process of cancelling then we can stop the timer too; after the next
                // update it won't get any more new pixels.
                if (status != Cancelling)
                {
                    updateTimer.stop();
                }
            }

            auto progress = renderer->Progress();
            if (progress > lastProgress)
            {
                lastProgress = progress;
                progressText.caption(BuildProgressMessage(lastProgress));
                UpdateBuffer();
                viewDrawing.update();
            }
        });

        updateTimer.start();
    }

    void MainForm::UpdateBuffer()
    {
        renderer->SnapshotTo(imageBuffer);

        // TODO: Just draw pixels that are new.
        for (unsigned int x = 0; x < imageBuffer.Width(); x++)
        {
            for (unsigned int y = 0; y < imageBuffer.Height(); y++)
            {
                auto colour = imageBuffer.GetPixel(x, y);
                color nanaColour{ static_cast<unsigned int>(255 * colour.R()), static_cast<unsigned int>(255 * colour.G()), static_cast<unsigned int>(255 * colour.B()) };
                graphicsBuffer.set_pixel(x, y, nanaColour);
            }
        }
    }
}
