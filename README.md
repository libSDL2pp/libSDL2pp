# libSDL2pp #

This library provides C++ bindings/wrappers for SDL2.

This library uses C++11!

## Synopsis ##

```c++
try {
  // Init SDL; will be automatically deinitialized when the object is destroyed
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  // Straightforward wrappers around corresponding SDL2 objects
  // These take full care of proper object destruction and error checking
  SDL2pp::Window window("libSDL2pp demo",
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        640, 480, SDL_WINDOW_RESIZABLE);
  SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL2pp::Texture sprite(renderer, SDL_PIXELFORMAT_ARGB8888,
                         SDL_TEXTUREACCESS_STATIC, 16, 16);

  unsigned char pixels[16 * 16 * 4];

  // Note proper constructor for Rect
  sprite.Update(SDL2pp::Rect(0, 0, 16, 16), pixels, 16 * 4);

  renderer.Clear();
  // Also note a way to specify null rects
  renderer.Copy(sprite, SDL2pp::Rect::Null(), SDL2pp::Rect::Null());
  renderer.Present();

  // You can still access wrapped C SDL types
  SDL_Renderer* sdl_renderer = renderer.Get();

  // Of course, C SDL2 API is still perfectly valid
  SDL_Delay(2000);

  // All SDL objects are released at this point or if an error occurs
} catch (SDL2pp::Exception& e) {
  // Exception stores SDL_GetError() result
  std::cerr << "Exception: " << e.what() << std::endl;
  std::cerr << "SDL Error: " << e.GetSDLError() << std::endl;
}
```

## Completeness ##

For now I only implement functionality I need myself, so the library
is not nearly complete. However, patches (as well as requests for
adding new functionality) are welcome.

## Building ##

Dependencies:
- cmake
- SDL2

To build standalone version:
```cmake . && make```

## Bundling ##

The library is easy to integrate into other CMake-using projects.

Just place the library into dedicated directory in your project
(for example, lib/SDL2pp) and add

```cmake
ADD_SUBDIRECTORY(lib/SDL2pp)
```
into your core CMakeLists.txt. This will act as similar to what
FIND_PACKAGE usually does, and will provide ${SDL2PP_INCLUDE_DIRS}
and ${SDL2PP_LIBRARIES} variables for your project. You will the
be able to use them as usual:

```cmake
INCLUDE_DIRECTORIES(${SDL2PP_INCLUDE_DIRS})

ADD_EXECUTABLE(mytarget ...)
TARGET_LINK_LIBRARIES(mytarget ${SDL2PP_LIBRARIES})
```

if bundled, libSDL2pp will not build a demo and will be a static
library, providing SDL2 includes/libs in the mentioned variables.

## Author ##

* [Dmitry Marakasov](https://github.com/AMDmi3) <amdmi3@amdmi3.ru>

## Contributors ##

* You name here!

## License ##

libSDL2pp comes under zlib license, the same license as SDL2.
