#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    MainForm::MainForm() : form(API::make_center(1280, 720), appear::decorate<appear::taskbar>())
    {
        caption("Rendering");

        text.create(*this, rectangle(nana::size(400, 100)));
        text.caption("Hello from the Rendering project!");
    }
}