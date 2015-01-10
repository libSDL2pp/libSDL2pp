# libSDL2pp #

[![Build Status](https://travis-ci.org/AMDmi3/libSDL2pp.svg?branch=master)](https://travis-ci.org/AMDmi3/libSDL2pp)

This library provides C++11 bindings/wrapper for SDL2 and satellite libraries.

## Synopsis ##

    try {
      // Init SDL; will be automatically deinitialized when the object is destroyed
      SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    
      // Straightforward wrappers around corresponding SDL2 objects
      // These take full care of proper object destruction and error checking
      SDL2pp::Window window("libSDL2pp demo",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            640, 480, SDL_WINDOW_RESIZABLE);
      SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
      SDL2pp::Texture sprite1(renderer, SDL_PIXELFORMAT_ARGB8888,
                             SDL_TEXTUREACCESS_STATIC, 16, 16);
      SDL2pp::Texture sprite2(renderer, "sprite.png"); // SDL_image support
    
      unsigned char pixels[16 * 16 * 4];
    
      // Note proper constructor for Rect
      sprite1.Update(SDL2pp::Rect(0, 0, 16, 16), pixels, 16 * 4);
    
      renderer.Clear();
    
      // Also note a way to specify null rects and points
      renderer.Copy(sprite1, SDL2pp::NullOpt, SDL2pp::NullOpt);
    
      // Copy() is overloaded, providing access to both SDL_RenderCopy and SDL_RenderCopyEx
      renderer.Copy(sprite2, SDL2pp::NullOpt, SDL2pp::NullOpt, 45.0);
    
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

## Features ##

Currently, the library provides wrapper classes for

* SDL
  * Library initialization/deinitialization
  * Audio
    * Audio device
    * WAV-related functions
    * SDL_AudioSpec
  * Graphics
    * SDL_Point
    * SDL_Rect
    * SDL_Renderer
    * SDL_Surface
    * SDL_Texture
    * SDL_Window
  * I/O
    * SDL_RWops
* SDL_image
  * Library initialization/deinitialization
  * Loading functions integrated into Texture and Surface
* SDL_ttf
  * Library initialization/deinitialization
  * TTF_Font (all functions covered)

each with subset of methods corresponding to SDL functions working
with sepcific type of object and in some cases additional convenience
methods. These classes support:

- RAII-style initialization and destruction
- Total error checking: exception is thrown if any SDL function fails.
  Exception itself allows to retrieve SDL error string
- C++11 move semantics support, which allow you to store SDL objects
  in containers and pass/return them by value with no overhead

Set of functional exensions above SDL2 is also available:

* RWops adapters for C++ containers and streams
* Optional object to safely handle values which may not be present,
  (for which SDL2 usually uses NULL pointers)

## Building ##

To build libSDL2pp, you need a compiler with C++11 support, for
example clang 3.4+ or gcc 4.8+.

Dependencies:
* cmake
* SDL2
* SDL_image2 (optional)
* SDL_ttf2 (optional)

To build standalone version:

    cmake . && make

Following variabled may be supplied to CMake to affect build:

* ```SDL2PP_WITH_IMAGE``` - enable SDL_image support (default ON)
* ```SDL2PP_WITH_TTF``` - enable SDL_ttf support (default ON)
* ```SDL2PP_WITH_WERROR``` - treat warnings as errors, useful for CI (default OFF)
* ```SDL2PP_CXXSTD``` - override C++ standard (default C++11). With C++1y some additional features are enabled such as usage of [[deprecated]] attribute and using stock experimental/optional from C++ standard library
* ```SDL2PP_WITH_EXAMPLES``` - enable building example programs (only for standalone build, default ON)
* ```SDL2PP_WITH_TESTS``` - enable building tests (only for standalone build, default ON)
* ```SDL2PP_ENABLE_GUI_TEST``` - enable tests which require X11 to run (only for standalone build, default ON)
* ```SDL2PP_WITH_2_0_4``` - enable experimental features available since SDL 2.0.4 (default OFF). These were not tested and may not even compile.

## Installation ##

To install the library systemwide, run:

    cmake . && make && make install

You can change installation prefix with CMAKE_INSTALL_PREFIX cmake
variable:

    cmake -DCMAKE_INSTALL_PREFIX=/usr/local . && make && make install

SDL2pp installs pkg-config file, so it can be used with any build
system which interacts with pkg-config, including CMake and GNU
Autotools.

SDL2pp is also already available from following package repositories:

* [Arch Linux AUR](https://aur.archlinux.org/packages/sdl2pp-git/)
* [FreeBSD ports](http://www.freshports.org/devel/sdl2pp/)

## Bundling ##

The library is easy to integrate into other CMake-using projects
(and as the library has no stable API yet, this way of using it is
still recommended).

Just place the library into dedicated directory in your project
(for example, lib/SDL2pp) and add

    SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
    SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
    ADD_SUBDIRECTORY(lib/SDL2pp)

into your core CMakeLists.txt. This will act as similar to what
FIND_PACKAGE usually does, and will provide ${SDL2PP_INCLUDE_DIRS}
and ${SDL2PP_LIBRARIES} variables for your project. You will then
be able to use them as usual:

    INCLUDE_DIRECTORIES(${SDL2PP_INCLUDE_DIRS})

    ADD_EXECUTABLE(mytarget ...)
    TARGET_LINK_LIBRARIES(mytarget ${SDL2PP_LIBRARIES})

if bundled, libSDL2pp does not build examples and becomes a static
library, providing required SDL2 includes/libs in the mentioned
variables.

## Completeness ##

Library still doesn't cover all aspects of SDL2, and the development
is generally guided by the author's needs and interest without a goal
for covering all SDL2 functions as soon as possible. However, if
you need specific bits which are not yet implemented in the library,
feel free to drop an issue. Patches are of course more than welcome.

It should be noted, however, that I currently do not plan to implement
any wrappers over non object-oriented SDL2 code, as these do not bring
any benefits over using plain C API. E.g. I see no point in implementing
SDL2pp::Delay() as it won't bring any convenience over SDL_Delay().

## Users ##

Projects using libSDL2pp:

* [OpenStrike](https://github.com/AMDmi3/openstrike) - Libre reimplementation of Jungle and Desert Strike games
* [OpenDaed](https://github.com/AMDmi3/opendaed) - Libre reimplementation of The Daedalus Encounter game

## Author ##

* [Dmitry Marakasov](https://github.com/AMDmi3) <amdmi3@amdmi3.ru>

## Contributors ##

* [Carl Schwope](https://github.com/Lowest0ne)

## License ##

libSDL2pp comes under zlib license, the same license as SDL2. See COPYING.txt.
