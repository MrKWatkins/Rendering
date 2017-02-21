#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "../MrKWatkins.Rendering/Renderer.h"
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/drawing.hpp>
#include "../MrKWatkins.Rendering/RandomAlgorithm.h"

using namespace nana;
using namespace paint;

namespace MrKWatkins::Rendering::UI
{
    class MainForm : public form
    {
        place layout{ *this };
        label text{ *this };
        panel<true> view{ *this };
        drawing viewDrawing { view };
        timer timer;

        double lastProgress = 0;
        graphics buffer;
        std::unique_ptr<Renderer> renderer;

        void UpdateBuffer();

    public:
        MainForm();
    };
}