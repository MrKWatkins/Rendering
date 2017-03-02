# Rendering - First Image #

Now we have an framework in place we can start on the ray tracing itself.

## Types for Geometry ##

First step is to add some types to handle geometry:

* Point. Represents a point in three dimensions.
* Vector. Represents a vector in three dimensions. Although very similar to a point as both have *x*, *y* and *z* components I've made them two different types as the things you can do with them are very different. For example the dot product of two points doesn't make sense for a point but it does for a vector.
* Ray. Definitely need one of these for a ray tracer... Consists of a point representing the origin of the ray and a vector indicating the direction. I've normalized the vector to make things a bit easier to work with.
* Object. Base class for all solid objects. Has an abstract method to determine the nearest intersection point with a ray. We will use this method in the ray tracer to work out what objects are in the path of our rays.
* Sphere. Implementation of Object representing a sphere which consists of a centre point and a radius.

I also thought it was about time I started writing some tests so I created a new project to hold tests written with the [Catch](https://github.com/philsquared/Catch) unit test framework. I chose this one as it isn't platform specific, is really easy to include (just add a single header file) and is supported by [ReSharper](https://www.jetbrains.com/resharper/)'s unit test runner.

## Intersection of Ray and Sphere ##

We need a bit of maths to work out the intersection point of a sphere and a ray. We can represent a ray with the following equation:

> **R** = **O** + *d***D**

Where:
* **R** is a vector to a point on the line.
* **O** is a vector to the origin of the ray.
* *d* is the length along the ray.
* **D** is a unit vector representing the direction of the ray.

We can represent a sphere with the equation:

> (**S** - **C**)**.**(**S** - **C**) = *r*²

Where:
* **S** is a vector to a point on the sphere.
* **C** is a vector to the centre of the sphere.
* *r* is the radius of the sphere.

The intersection(s) happen when **S** = **R** or:

> (**O** + *d***D** - **C**)**.**(**O** + *d***D** - **C**) = *r*²

If we let **X** = **O** - **C** and then expand and rearrange we get:

> *d*²**D.D** + 2*d***D.M** + **M.M** = *r*²

Which is a quadratic equation of the form *ad*² + *bd* + *c* = 0 where:

* *a* = **D.D** = 1 as **D** is a unit vector.
* *b* = 2**D.M**
* *c* = **M.M** - *r*²

Substituting in and simplifying gives us the solutions:

> *d* = -**D.M** ± √((**D.M**)² - **M.M** + *r*²)

If the value in the root is less than zero then there are no (real) solutions. If it is exactly zero then the ray hits the sphere only once at the tangent, otherwise there are two solutions where it hits one side of the sphere, passes through then hits the other side.

None of the above takes into account the origin of the ray however. Firstly it would be handy to know if the origin of the ray was *inside* the sphere. For the moment I will treat this as an error in the code as I don't want my spheres crossing the view. **M** is the vector between the sphere's centre and the ray's origin. If the length of this vector, i.e. the distance from the sphere centre to the ray origin, is less than the sphere's radius then the ray must start inside the sphere. I.e. the ray starts inside the sphere if:

> **|M|** - *r* <= 0

Given the length of a vector is √**M.M** we can rewrite this as:

> **M.M** - *r*² <= 0 or *c* <= 0

Secondly we need to know which is the intersection closest to the ray's origin if there are two solutions. From the equation of the ray this is simply the smallest value of *d*, i.e. the smallest of the two solutions. As the result of the square root will always be positive the smallest solution will be the one that subtracts the square root.

Thirdly what if the sphere is entirely behind the ray? For this to happen *d* would have to be negative - we can therefore discard our solution if it's less than zero. And we can ignore one solution being less than zero and one greater than zero as that would imply we're inside the sphere, which we've already discarded.

## Types for Ray Tracing ##

Now we can actually work out where a sphere and a ray intersect it's possible to do some ray tracing. To do this I needed a few more types:

* SceneObject. This is an object in a scene to be rendered. Our Object class is just pure geometry; this extends takes an Object and adds some real world properties. Only one so far - colour.
* Scene. Details of a scene. Currently comprises a background colour and a vector of SceneObjects.
* RayTracer. This is our implementation of the Algorithm class for ray tracing. It takes a Scene in the constructor. When RenderPoint is called it creates a ray from that point directed along the positive z-axis, or into the screen. It then loops through all the objects in the scene, finds the one with the closest intersection point and uses it's colour for the point. If it does intersect with any of the objects then it uses the background colour for the scene instead.

## First Image ##

With all this in place I was able to create my first image, of a scene comprising a single sphere in the centre of the view:

![First Image](/../Images/2017-03-02 First Image.png)

Impressive huh? Well no, not really. But it's a start...

## Thoughts ##

* Still not 100% sure on the semantics around unique_ptrs... I ended up having to use a shared_ptr for my vector of scene objects when I really want unique_ptrs as they are children of the scene. I'll read up on it all a bit further down the line and come back and refactor.
* Catch doesn't allow two tests with the same name, even if they're in different namespaces, which is annoying.
* Going to upgrade to Visual Studio 2017 as soon as I can because that supports the new [std::optional](http://en.cppreference.com/w/cpp/utility/optional) type whereas 2015 doesn't; I've had to roll my own Optional type for the moment. (Used when returning the nearest intersection point - there might not be one)

The code so far can be found [on GitHub](https://github.com/MrKWatkins/Rendering/tree/first-image). Next step is to start look at some shading and lighting.