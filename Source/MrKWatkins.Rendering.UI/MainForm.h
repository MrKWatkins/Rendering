#pragma once
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    class MainForm :
        public form
    {
        label text;
    public:
        MainForm();
    };
}