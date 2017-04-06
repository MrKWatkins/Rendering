#include "stdafx.h"
#include "MainForm.h"
#include <Scene.h>
#include <RayTracing.h>
#include <Phong.h>
#include <Flat.h>
#include <SkyGradient.h>
#include <Chequerboard.h>

using namespace nana;
using namespace MrKWatkins::Rendering::Shading;

namespace MrKWatkins::Rendering::UI
{
	void MainForm::Layout() const
    {
        place layout{ *this };
        layout.div("margin=10 gap=10 vert<weight=35 <weight=130 margin=[5,0,0,0] progressText><margin=[5,0,0,0] statusText><weight=100 margin=[0,0,10,10] save><weight=100 margin=[0,0,10,10] cancel>><view>");
        layout["progressText"] << progressText;
        layout["statusText"] << statusText;
        layout["view"] << view;
        layout["save"] << save;
        layout["cancel"] << cancel;
        layout.collocate();
    }

    std::string MainForm::BuildProgressMessage(double progress)
    {
        return "Progress: " + std::to_string(progress * 100) + "%";
    }

	std::unique_ptr<Scene::Scene> BuildScene()
	{
		auto scene = std::make_unique<Scene::Scene>(Colour(0.25, 0.25, 0.25), Texture::Create<SkyGradient>(Colour(0.8, 1, 1), Colour(0, 0.2, 0.8)));

		Material red = Material::Build(Colour(0.1, 0.01, 0.01), Colour(1, 0, 0)).WithReflectivity(0.1);
		Material black = Material::Build(Colour(0.01, 0.01, 0.01), Colour(0, 0, 0)).WithReflectivity(0.2);
		scene->AddPlane(Plane(Point(0, 0, 0), Vector(0, 1, 0)), Texture::Create<Chequerboard>(red, black, 0.25));

		scene->AddSphere(Sphere(0.1, 0.2, 0.75, 0.2), Material::Chrome());
		scene->AddSphere(Sphere(0.5, 0.5, 0.75, 0.2), Material::Chrome());
		scene->AddSphere(Sphere(0.9, 0.2, 0.75, 0.2), Material::Chrome());

		scene->AddTriangle(Triangle(Point(0.1, 0.4, 0.1), Point(0.2, 0.4, 0.5), Point(0.2, 0.9, 0.5)), Material::Bronze());
		scene->AddTriangle(Triangle(Point(0.6, 0.0, 0.05), Point(0.6, 0.3, 0.05), Point(0.5, 0.0, 0.05)), Material::Jade());

		scene->AddPointLight(Point(1, 1, 0), Attenuation::InverseSquare(20), Colour(1, 1, 1));
		scene->AddPointLight(Point(0, 1, 0), Attenuation::InverseSquare(10), Colour(0.5, 0.5, 0));

		return scene;
	}

    MainForm::MainForm() : form(API::make_center(740, 775), appear::decorate<appear::taskbar>()), imageBuffer { 720, 720 }
    {
        graphicsBuffer = { nana::size{ 720, 720 } };
        graphicsBuffer.make(nana::size{ 720, 720 });

		auto shadingModel = ShadingModel::Create<Phong>();

        renderer = Renderer::Start<Algorithms::RayTracing>(720, std::move(shadingModel), std::move(BuildScene()), 1);

        caption("Rendering");
        progressText.caption(BuildProgressMessage(0));
        save.enabled(false);

        Layout();

        save.events().click([&]
        {
            filebox fb{ *this, false };
            fb.add_filter("PNG (*.png)", "*.png");
            fb.init_path("%USERPROFILE%\\Desktop");

            if (fb())
            {
                auto file = fb.file();
                graphicsBuffer.save_as_file(file.c_str());
            }
        });

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
                save.enabled(true);

				// If we've errored pop up a message box.
				if (status == Error)
				{
					statusText.caption("Error: " + renderer->StatusMessage());
					statusText.fgcolor(colors::dark_red);
				}
				else if (status == Finished)
				{
					statusText.caption("Finished: " + renderer->StatusMessage());
				}

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
