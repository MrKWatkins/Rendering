#include "stdafx.h"
#include "MainForm.h"
#include <nana/gui.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/detail/inner_fwd_implement.hpp>
#include "../MrKWatkins.Rendering/Scene.h"
#include "../MrKWatkins.Rendering/RayTracing.h"
#include "../MrKWatkins.Rendering/Lambertian.h"

using namespace nana;

namespace MrKWatkins::Rendering::UI
{
    void MainForm::Layout() const
    {
        place layout{ *this };
        layout.div("margin=10 gap=10 vert<weight=35 <margin=[5,0,0,0] progressText><weight=100 margin=[0,0,10,10] cancel>><view>");
        layout["progressText"] << progressText;
        layout["view"] << view;
        layout["cancel"] << cancel;
        layout.collocate();
    }

    std::string MainForm::BuildProgressMessage(double progress)
    {
        return "Progress: " + std::to_string(progress * 100) + "%";
    }

    MainForm::MainForm() : form(API::make_center(740, 775), appear::decorate<appear::taskbar>()), imageBuffer { 720, 720 }
    {
        graphicsBuffer = { nana::size{ 720, 720 } };
        graphicsBuffer.make(nana::size{ 720, 720 });

        auto shadingModel = std::unique_ptr<Shading::ShadingModel>(std::make_unique<Shading::Lambertian>());

        auto scene = std::make_unique<Scene::Scene>(Colour(0, 0, 0), Colour(0.2, 0.2, 0.2));
        scene->AddPlane(Geometry::Plane(Geometry::Point(0, 0, 0), Geometry::Vector(0, 1, 0)), Colour(1, 1, 1));
        scene->AddSphere(Geometry::Sphere(0.5, 0.5, 0.5, 0.1), Colour(0, 0, 1));
        scene->AddSphere(Geometry::Sphere(0.2, 0.2, 1.25, 0.2), Colour(1, 0, 0));
        scene->AddPointLight(Geometry::Point(1, 1, 0), Colour(1, 1, 1));

        /*for (auto f = 0.1; f<= 1.0; f+= 0.1)
        {
            scene->AddSphere(Geometry::Sphere(0, 0, f, 0.01), Colour(1, 0, 0));
            scene->AddSphere(Geometry::Sphere(1, 0, f, 0.01), Colour(1, 1, 0));
            scene->AddSphere(Geometry::Sphere(0, 1, f, 0.01), Colour(1, 0, 1));
            scene->AddSphere(Geometry::Sphere(1, 1, f, 0.01), Colour(1, 1, 1));

            scene->AddSphere(Geometry::Sphere(f, f, 1, 0.01), Colour(0, 1, 0));
            scene->AddSphere(Geometry::Sphere(1-f, f, 1, 0.01), Colour(0, 1, 0));
        }*/

        renderer = Renderer::Start<Algorithms::RayTracing>(720, std::move(shadingModel), std::move(scene), 1);

        caption("Rendering");
        progressText.caption(BuildProgressMessage(0));
        cancel.caption("Cancel");

        Layout();

        cancel.events().click([&]
        {
            renderer->Cancel();
        });

        view.bgcolor(colors::black);
        viewDrawing.draw_diehard([&](graphics& graphics)
        {
            graphicsBuffer.stretch(graphics, rectangle(graphics.size()));
        });

        updateTimer.interval(1000);
        updateTimer.elapse([&]()
        {
            auto status = renderer->Status();
            if (status != InProgress)
            {
                // Disable cancel if we're no longer in progress.
                cancel.enabled(false);

                // If we're not still in the process of cancelling then we can stop the timer too; after the next
                // update it won't get any more new pixels.
                if (status != Cancelling)
                {
                    updateTimer.stop();
                }
            }

            auto progress = renderer->Progress();
            if (progress > lastProgress)
            {
                lastProgress = progress;
                progressText.caption(BuildProgressMessage(lastProgress));
                UpdateBuffer();
                viewDrawing.update();
            }
        });

        updateTimer.start();
    }

    void MainForm::UpdateBuffer()
    {
        renderer->SnapshotTo(imageBuffer);

        // TODO: Just draw pixels that are new.
        for (unsigned int x = 0; x < imageBuffer.Width(); x++)
        {
            for (unsigned int y = 0; y < imageBuffer.Height(); y++)
            {
                auto colour = imageBuffer.GetPixel(x, y);
                color nanaColour{ static_cast<unsigned int>(255 * colour.R()), static_cast<unsigned int>(255 * colour.G()), static_cast<unsigned int>(255 * colour.B()) };
                graphicsBuffer.set_pixel(x, y, nanaColour);
            }
        }
    }
}
