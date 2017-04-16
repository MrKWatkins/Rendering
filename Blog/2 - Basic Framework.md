First step was to get a basic framework in place that can render an image and preview it in the GUI. I added a separate project for all the rendering code, keeping all the display stuff in the GUI project. Helps separate concerns and will make it easier to, for example, generate a command line renderer later on.

## Types for Creating Images ##

I added a few types to the project to handle storing and creating images:

* `Colour`. Decided it would be best to have my own colour type to avoid tying me into Nana's drawing types. The colour is in RGB format with each component a double in the range 0 -> 1; should keep the maths a bit simpler than 0 -> 255 and it will allow me a greater precision.
* `Image`. Represents an image, i.e. a square grid of pixels, each of which is simply a `Colour`. `Image` is immutable.
* `MutableImage`. An extension to image that can be updated. Includes a method for setting a given pixel. `Image`s can also be copied into `MutableImage`s - allows us to reserve memory for a buffer for example, and then copy another image into it rather than repeatedly releasing and reallocating memory.

## Types for Rendering ##

The rendering itself consists of two main types:

* `Algorithm`. This is an abstract class with a single method, `RenderPoint`. This takes (x, y) co-ordinates in the range (0, 0) -> (1, 1) and returns a `Colour` object representing the colour at that point. The range is normalised so that the algorithm doesn't need know about the image size - whatever uses the algorithm can map the image pixels to the 0 -> 1 range. This might all need to change of course when I start thinking about cameras and the like, plus it currently assumes a square image, but it's good enough for now. 
I've added two algorithms for testing:
 * `Random`. Returns a random colour each call to `RenderPoint`.
 * `Gradient`. Renders a gradient from one colour in the top left to a second colour in the bottom right.
* `Renderer`. This generates an image by running a given algorithm for each pixel on a background thread. It includes members for querying the state of the render, (e.g. the status or progress complete) cancelling and taking a snapshot of the current image.

## Types for the UI ##

Just a single one here:

* `MainForm`. This displays the progress, has a cancel button and displays the current image in a preview window. A timer runs to periodically update the progress and image.

## Thoughts So Far ##

* It's all a bit rough and ready at the moment, partly because I'm new to C++ and partly because it's all a bit boring really - the rendering itself is the interesting part! I'll come back and tidy it up when I know C++ a bit better and have a better idea of what is needed for the project itself.
* The C++ compiler has some fairly unhelpful error messages... Errors often point to the wrong place, e.g. I've had errors around unique pointers that give a line in <memory> from the STL, which is not at all useful...
* The C++ linker has some *really* unhelpful error messages... The stand out one so far was [LNK2019](https://msdn.microsoft.com/en-us/library/799kze2z.aspx) with an accompanying gibberish message. I received this in the UI project because I had a template method in the rendering project whose implementation was in a .cpp file rather than all being in the header file.
* If someone wrote a webpage for C++ beginners with a list of error messages and *what they actually mean* I would be very grateful!

The code so far can be found [on GitHub](https://github.com/MrKWatkins/Rendering/tree/basic-framework). Next step is to start on an algorithm to render a scene.