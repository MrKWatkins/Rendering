// stdafx.h : include file for standard system include files, or project specific include files that are used frequently, but are changed infrequently.
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Nana.
#include <nana/gui.hpp>
#include <nana/gui/detail/inner_fwd_implement.hpp>
#include <nana/gui/drawing.hpp>
#include <nana/gui/filebox.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/threads/pool.hpp>