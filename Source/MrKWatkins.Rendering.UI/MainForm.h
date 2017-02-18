#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "../MrKWatkins.Rendering/Renderer.h"
#include <nana/gui/timer.hpp>
#include <nana/threads/pool.hpp>

using namespace nana;
using namespace paint;

namespace MrKWatkins::Rendering::UI
{
    class MainForm :
        public form
    {
        threads::pool threadPool;
        place layout{ *this };
        label text{ *this };
        panel<true> view{ *this };
        timer timer;

        Renderer renderer{ 320, 240 };

        graphics GetImage() const;
        void RefreshImage();

    public:
        MainForm();
    };
}