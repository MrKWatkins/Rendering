# Third Part Code #

This folder contains third party code use by the project. The code is included as-is in the relevant folder - anything extra I've need to add (e.g. project files) I've tried to keep separate by including in this folder.

## ZLib ##

Compression library, needed for PNG image compression. Downloaded from [http://zlib.net/](http://zlib.net/). I've created a custom project file at zlib.vcxproj based on contrib\vstudio\vc14\zlibstat.vcxproj with the following changes:
* Removes Itanium and Release versions.
* Renamed ReleaseWithoutAsm to just Release; the build is much simpler using the versions without hand-rolled assembly and I don't really need the extra little bit of speed.
* Updated the runtime libraries to use non-DLL versions.
* Removed ZLIB_WINAPI pre-processor definition to stop linker errors. (See [http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib](http://stackoverflow.com/questions/5424549/unresolved-externals-despite-linking-in-zlib-lib)
* Renamed the output from zlibstat to just zlib.
* Added an exception for compiler warning [C4267](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4267) to keep my output window clean.
* Use an MSBuild variable to define the ZLib source folder.
* Removed unnecessary /MACHINE setting from the librarian additional options.