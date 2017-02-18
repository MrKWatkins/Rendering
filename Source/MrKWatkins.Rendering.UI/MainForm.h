#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "../MrKWatkins.Rendering/Renderer.h"
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/drawing.hpp>

using namespace nana;
using namespace paint;

namespace MrKWatkins::Rendering::UI
{
    class MainForm : public form
    {
        threads::pool threadPool;
        place layout{ *this };
        label text{ *this };
        panel<true> view{ *this };
        drawing viewDrawing { view };
        timer timer;

        graphics buffer{ nana::size{ 320, 240 } };
        Renderer renderer{ 320, 240 };

        void UpdateBuffer();

    public:
        MainForm();
    };
}