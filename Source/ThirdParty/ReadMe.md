# Third Party Code #

This folder contains third party code use by the project. The code is included as-is in the relevant folder - anything extra I've need to add (e.g. project files) I've tried to keep separate by including in this folder.

## zlib ##

Compression library, needed for PNG image compression. Downloaded from [http://zlib.net/](http://zlib.net/). I've created a custom project file at `zlib.vcxproj` based on `contrib\vstudio\vc14\zlibstat.vcxproj` with the following changes:

* Removes Itanium and Release versions.
* Renamed ReleaseWithoutAsm to just Release; the build is much simpler using the versions without hand-rolled assembly and I don't really need the extra little bit of speed.
* Updated the runtime libraries to use non-DLL versions.
* Removed `ZLIB_WINAPI` preprocessor definition to stop linker errors. (See [http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib](http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib)
* Renamed the output from `zlibstat` to just `zlib`.
* Added an exception for compiler warning [C4267](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4267) to keep my output window clean.
* Use an MSBuild variable to define the ZLib source folder.
* Removed unnecessary `/MACHINE` setting from the librarian additional options.

## libpng ##

Library for loading and saving PNG images. Downloaded from [http://www.libpng.org/pub/png/libpng.html](http://www.libpng.org/pub/png/libpng.html). I've created a custom project file at `libpng.vcxproj` based on `projects\vstudio\libpng\libpng.vcxproj` with the following changes:

* Removed the Debug and Release dynamic library configurations.
* Renamed the Debug Library and Release Library configurations to just Debug and Release.
* Added x64 versions.
* Removed the version number from the target name.
* Removed reference to `zlib.props` - I define the path to the zlib source in the project file instead.
* libpng auto-generates the header file `pnglibconf.h` from `\scripts\pnglibconf.h.prebuilt`. There is a project to do that at `projects\vstudio\pnglibconf\pnglibconf.vcxproj` - it just copies and renames the file with a custom build step. I've put that build step into my project file and make it run before compilation.

## nana ##

GUI library used to create the user interface. Downloaded from [http://nanapro.org/en-us/](http://nanapro.org/en-us/).  I've created a custom project file at `nana.vcxproj` based on `build\vc2015\nana.vcxproj` with the following changes:

* Tidied up the output paths and files.
* Added `STD_CODECVT_NOT_SUPPORTED` to the preprocessor definitions. C++17 deprecates `<codecvt>`; adding this flag stops `charset.cpp` from using it.
* Added `NANA_ENABLE_PNG` to enabled PNG support.
* Added a custom build task to copy the necessary libpng header files across from the libpng source folder into the temporary `nana_extrlib` folder.
* Added the `nana_extrlib` folder to the include folders.
