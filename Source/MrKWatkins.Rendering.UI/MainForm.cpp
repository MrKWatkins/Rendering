#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/detail/inner_fwd_implement.hpp>
#include "../MrKWatkins.Rendering/RandomAlgorithm.h"

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    MainForm::MainForm() : form(API::make_center(720, 745), appear::decorate<appear::taskbar>()), imageBuffer { 700, 700 }
    {
        graphicsBuffer = { nana::size{ 700, 700 } };
        renderer = Renderer::Start(700);
        caption("Rendering");

        layout.div("margin=10 gap=10 vert<text weight=25><picture>");

        text.caption("Hello from the Rendering project!");
        layout["text"] << text;

        view.bgcolor(colors::black);

        layout["picture"] << view;

        layout.collocate();

        viewDrawing.draw_diehard([&](graphics& graphics)
        {
            graphicsBuffer.stretch(graphics, rectangle(graphics.size()));
        });

        timer.interval(250);
        timer.elapse([&]()
        {
            auto progress = renderer->Progress();
            if (progress > lastProgress)
            {
                lastProgress = progress;
                UpdateBuffer();
                viewDrawing.update();
            }
        });
        timer.start();
    }

    void MainForm::UpdateBuffer()
    {
        renderer->SnapshotTo(imageBuffer);

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