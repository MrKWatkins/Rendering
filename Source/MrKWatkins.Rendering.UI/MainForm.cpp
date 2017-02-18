#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/detail/inner_fwd_implement.hpp>

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    MainForm::MainForm() : form(API::make_center(1280, 720), appear::decorate<appear::taskbar>())
    {
        caption("Rendering");

        layout.div("margin=10 gap=10 vert<text weight=25><picture>");

        text.caption("Hello from the Rendering project!");
        layout["text"] << text;

        view.bgcolor(colors::black);

        layout["picture"] << view;

        layout.collocate();

        viewDrawing.draw_diehard([&](graphics& graphics)
        {
            buffer.stretch(graphics, rectangle(graphics.size()));
        });

        timer.interval(100);
        timer.elapse([&]()
        {
            UpdateBuffer();
            viewDrawing.update();
        });
        timer.start();
    }

    void MainForm::UpdateBuffer()
    {
        renderer.Render();
        const auto& image = renderer.Image();

        for (unsigned int x = 0; x < image.Width(); x++)
        {
            for (unsigned int y = 0; y < image.Height(); y++)
            {
                auto colour = image.Pixel(x, y);
                color nanaColour{ static_cast<unsigned int>(255 * colour.R()), static_cast<unsigned int>(255 * colour.G()), static_cast<unsigned int>(255 * colour.B()) };
                buffer.set_pixel(x, y, nanaColour);
            }
        }
    }
}