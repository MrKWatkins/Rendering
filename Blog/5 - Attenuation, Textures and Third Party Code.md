# Rendering - Attenuation, Textures and Third Party Code #

To make the scenes a bit more interesting the next step is to add some more realistic lighting and some textures.

## Attenuation ##

When modelling [Lambertian Reflectance](4 - Plane Shading#Lambertian Reflectance) I made the lights have constant intensity, i.e. the intensity at the point on the surface \\\( I \\\) was always 1. In reality the intensity of a light diminishes with distance from the source. To model this all the lights now take an Attenuation instance which is used to determine the intensity at a distance from the light. Rather than have separate sub classes for each type of attenuation I've made the Attenuation type take a function that gives the intensity; there are then static methods to create the various different attenuations. This seemed a simpler approach given the attenuation is just a single, simple function.

We'd expect the intensity to fall off as an inverse square law. As well as creating an inverse square attenuation I've also added linear and inverse. We can demonstrate their difference by rendering three spot lights just above a plane; from left to right, linear, inverse and inverse square:

![Attenuations](/../Images/2017-03-10 Attenuations.png)

## Textures ##

Currently we determine the colour of our surface at a given point by just taking a single colour. I've now made this a bit more general with a Material class. This is basically a function that gives the colour at a given point. Currently the materials are simple and don't know anything about the geometry of the object they're for - I can see this might change in the future, e.g. mapping a texture to a sphere will involve needing knowledge of the size of the sphere. There are currently three materials:

* `Solid`. Just a single colour, as before essentially.
* `Chequerboard`. A repeating chequerboard of two colours. Determining the colour at a given point is simply a matter of dividing each of the \\\( x \\\), \\\( y \\\) and \\\( z \\\) (our chequerboard is really 3D, with cubes rather than squares...) co-ordinates by the size of the squares (cubes!) to get the number of the square in each direction. We then add these three numbers - if the total is even we return one colour, if it's odd we return another.
* `SkyGradient`. I've also made the background for the scene a material. Now we project the ray long into the distance if there are no intersections and use that co-ordinate with a material to work out the background colour. `SkyGradient` is designed to be used for the background. It's two colours, one at the horizon and one at the zenith. To work out the colour at a given point we just work out the angle from the horizon and interpolate between the two colours based on the size of the angle.

Putting these textures in our scene gets us a bit close to the obligatory 'reflective spheres on a chequerboard' all ray tracers must render:

![Chequerboard and Sky](/../Images/2017-03-06 Chequerboard and Sky.png)

## Third Party Code ##

Now I'm creating more images I wanted to make it easier to save them - before I was taking a screen grab of the UI and manually cropping it to just the image. [nana](http://nanapro.org) has support for PNG files, however you need to include some third party code, namely [libpng](http://www.libpng.org/pub/png/libpng.html) and [zlib](http://zlib.net). (libpng uses zlib for compression)

There are pre-built static libraries available [on the Nana website](https://sourceforge.net/projects/nanapro/files/extrlib/) however I thought I would build them from scratch myself. Partly to give myself a bit more experience with building C++ stuff, partly to (hopefully!) make it easier to build on other platforms and partly to avoid the compiler warnings I got about missing .pdb files when I did use the static libraries...

I therefore downloading the source for them and put them into a ThirdParty folder under the source tree. I also decided to move the nana code into the same folder. And upgrade to Visual Studio 2017 whilst I was at it. I've tried to not change the downloaded source at all if possible to make it easier to upgrade to newer versions; this means I've created new project files for each library. Here are some notes on what I had to do to get everything building:

### zlib ###

Downloaded from [http://zlib.net/](http://zlib.net/). I've created a custom project file at `zlib.vcxproj` based on `contrib\vstudio\vc14\zlibstat.vcxproj` with the following changes:

* Removes Itanium and Release versions.
* Renamed ReleaseWithoutAsm to just Release; the build is much simpler using the versions without hand-rolled assembly and I don't really need the extra little bit of speed.
* Updated the runtime libraries to use non-DLL versions.
* Removed `ZLIB_WINAPI` preprocessor definition to stop linker errors. (See [http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib](http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib)
* Renamed the output from `zlibstat` to just `zlib`.
* Added an exception for compiler warning [C4267](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4267) to keep my output window clean.
* Use an MSBuild variable to define the ZLib source folder.
* Removed unnecessary `/MACHINE` setting from the librarian additional options.

### libpng ###

Downloaded from [http://www.libpng.org/pub/png/libpng.html](http://www.libpng.org/pub/png/libpng.html). I've created a custom project file at `libpng.vcxproj` based on `projects\vstudio\libpng\libpng.vcxproj` with the following changes:

* Removed the Debug and Release dynamic library configurations.
* Renamed the Debug Library and Release Library configurations to just Debug and Release.
* Added x64 versions.
* Removed the version number from the target name.
* Removed reference to `zlib.props` - I define the path to the zlib source in the project file instead.
* libpng auto-generates the header file `pnglibconf.h` from `\scripts\pnglibconf.h.prebuilt`. There is a project to do that at `projects\vstudio\pnglibconf\pnglibconf.vcxproj` - it just copies and renames the file with a custom build step. I've put that build step into my project file and make it run before compilation.

### nana ###

Downloaded from [http://nanapro.org/en-us/](http://nanapro.org/en-us/).  I've created a custom project file at `nana.vcxproj` based on `build\vc2015\nana.vcxproj` with the following changes:

* Tidied up the output paths and files.
* Added `STD_CODECVT_NOT_SUPPORTED` to the preprocessor definitions. C++17 deprecates `<codecvt>`; adding this flag stops `charset.cpp` from using it.
* Added `NANA_ENABLE_PNG` to enabled PNG support.
* Added a custom build task to copy the necessary libpng header files across from the libpng source folder into the temporary `nana_extrlib` folder.
* Added the `nana_extrlib` folder to the include folders.


The code so far can be found [on GitHub](https://github.com/MrKWatkins/Rendering/tree/attenuation-and-textures). Next I'll look at adding a better lighting model so I can start rendering reflections.