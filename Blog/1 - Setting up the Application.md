# Rendering #

I've decided I need a pet project to practice my coding and to help me (finally!) learn C++. I've been interested in [ray tracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) for years now, ever since I got my hands on a copy of Imagine for my Amiga 1200. So my initial idea was to create a simple ray tracer as it will also teach me about 3D graphics. I then, as all good programmers do, decided to generalise that to rendering in general... So I'm going to start with a ray tracer and then move on to other rendering algorithms such as [photon mapping](https://en.wikipedia.org/wiki/Photon_mapping).

## GUI Framework ##

I've decided I'll need a GUI for the ray tracer so I can see what is being drawn as it's being drawn - I don't want to wait 10 hours for a render only to find I've got a blank image... Whilst I'll be doing the majority of development in Windows and Visual Studio (I'm a C# developer by day so I'll stick with the IDE I know) it would be nice if I could make it run on other platforms too as it would be handy to know how to write a Linux application too. For now I'll just get it running on Windows, but I'll use a cross-platform UI framework so I don't tie myself to Windows.

After looking around I plumped for [Nana](http://nanapro.org). The main reasons being:

- Looking at the code examples it seems fairly simple and straightforward.
- It uses native controls for it's rendering so my application will look like other applications for the target OS.
- Built with standard, modern C++ so I won't have any issues using the smart pointers or the STL with it.
- Thread safe - important as I'll want my rendering to be done over multiple threads where possible.
- Free with simple licensing.

Downside is that the documentation seems to be a bit hit and miss but as I'm not planning on doing anything too complicated GUI wise hopefully that won't be an issue.

## Setting up the Application ##

I managed to setup a Windows application using Nana for the GUI fairly easily which surprised me given the amount of options C++ projects seem to have and my current knowledge of the language in general... Here are the steps I took:

- Downloaded the [Nana source code](https://sourceforge.net/projects/nanapro/files/latest/download) and unzipped it in my source folder.
- Created a blank solution in Visual Studio 2015.
- Added the build\vc2015\nana.vcxproj project to the solution.
- Added a new C++ Win32 Project to the solution for my Windows application.
- Referenced the Nana project from the Win32 project.
- For each of the four solution configurations (debug and release for both x86 and x64) I made the following changes to the properties of the Win32 project:
 - Configuration Properties -> VC++ Directories -> Include Directories -> added the path to the Nana project' include folder. (For me this was `$(SolutionDir)nana-1.4.1\include`) Without this the compiler will not recognise include directives such as `#include <nana/gui.hpp>`.
 - Configuration Properties -> C/C++ -> Code Generation -> Runtime Library -> changed this to "Multi-threaded Debug (/MTd)" for the debug configurations and "Multi-threaded (/MT)" for the release configurations.
- Copied the [introduction code](http://nanapro.org/en-us/blog/2016/05/an-introduction-to-nana-c-library/) into the main .cpp file for my Win32 application with a few changes:
 - The introduction code is placed in a `main` function - as this is a Win32 application I move that code into the `wWinMain` function that already existed in the file, replacing everything there.
 - Added a `return 0;` at the end of `wWinMain` as it expects an `int` to be returned.

And that was it! Building and running the Win32 application gave me a nice little Nana generated window. Find the source for the project [on GitHub](https://github.com/MrKWatkins/Rendering/tree/blank-application).

Next I'll try and actually draw something!