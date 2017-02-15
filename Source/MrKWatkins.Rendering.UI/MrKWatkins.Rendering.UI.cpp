// MrKWatkins.Rendering.UI.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "MrKWatkins.Rendering.UI.h"
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

using namespace nana;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    form fm;
    fm.caption("Rendering");

    label lb{ fm, rectangle{ 10, 10, 200, 100 } };
    lb.caption("Hello from the Rendering project!");

    fm.show();

    exec();

    return 0;
}