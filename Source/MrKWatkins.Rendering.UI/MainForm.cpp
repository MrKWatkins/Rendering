#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <time.h>
#include <nana/gui/detail/inner_fwd_implement.hpp>
#include <nana/threads/pool.hpp>

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

        RefreshImage();

        timer.interval(1000);
        timer.elapse([&]()
        {
            RefreshImage();
        });
        timer.start();
    }

    void MainForm::RefreshImage()
    {
        time_t timer;
        auto before = time(&timer);

        renderer.Render();

        auto after = time(&timer);
        OutputDebugStringA(("Render took " + std::to_string(difftime(after, before)) + "\r\n").c_str());

        before = time(&timer);

        drawing dw(view);

        dw.draw([=](graphics& graphics)
        {
            auto image = GetImage();
            image.stretch(graphics, rectangle { graphics.size()});
        });   
        dw.update();

        after = time(&timer);
        OutputDebugStringA(("Redraw took " + std::to_string(difftime(after, before)) + "\r\n").c_str());
    }

    graphics MainForm::GetImage() const
    {
        const auto& image = renderer.Image();

        graphics buffer{ nana::size{ image.Width(), image.Height() } };
        for (unsigned int x = 0; x < image.Width(); x++)
        {
            for (unsigned int y = 0; y < image.Height(); y++)
            {
                auto colour = image.Pixel(x, y);
                color nanaColour{ static_cast<unsigned int>(255 * colour.R()), static_cast<unsigned int>(255 * colour.G()), static_cast<unsigned int>(255 * colour.B()) };
                buffer.set_pixel(x, y, nanaColour);
            }
        }

        return buffer;
    }
}