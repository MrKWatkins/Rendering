#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "../MrKWatkins.Rendering/Renderer.h"
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/drawing.hpp>
#include <nana/gui/widgets/button.hpp>

using namespace nana;
using namespace paint;

namespace MrKWatkins::Rendering::UI
{
    class MainForm : public form
    {
        label progressText{ *this };
        button cancel{ *this };
        panel<true> view{ *this };
        drawing viewDrawing { view };
        timer updateTimer;

        double lastProgress = 0;
        MutableImage imageBuffer;
        graphics graphicsBuffer;
        std::unique_ptr<Renderer> renderer;

        void Layout() const;
        static std::string BuildProgressMessage(double progress);
        void UpdateBuffer();

    public:
        MainForm();
    };
}