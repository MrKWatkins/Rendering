#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/drawing.hpp>
#include <nana/gui/widgets/button.hpp>
#include <Renderer.h>

using namespace nana;
using namespace paint;

namespace MrKWatkins::Rendering::UI
{
    class MainForm final : public form
    {
        label progressText{ *this };
        button save{ *this, "Save" };
        button cancel{ *this, "Cancel" };
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