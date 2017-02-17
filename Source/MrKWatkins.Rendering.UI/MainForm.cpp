#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include "PlaceHelper.h"

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    MainForm::MainForm() : form(API::make_center(1280, 720), appear::decorate<appear::taskbar>())
    {
        caption("Rendering");

        layout.div(PlaceHelper::EncloseWithPadding("<text>", 10).c_str());

        text.caption("Hello from the Rendering project!");
        layout["text"] << text;

        layout.collocate();
    }
}