// MrKWatkins.Rendering.UI.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include "../MrKWatkins.Rendering/Renderer.h"
#include "MainForm.h"

using namespace nana;
using namespace MrKWatkins::Rendering::UI;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    MainForm mainForm;
    mainForm.show();

    exec();

    return 0;
}