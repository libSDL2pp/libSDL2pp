<a href="https://repology.org/metapackage/libsdl2pp/versions">
    <img src="https://repology.org/badge/vertical-allrepos/libsdl2pp.svg" alt="libsdl2pp packaging status" align="right">
</a>

[![CI](https://github.com/libSDL2pp/libSDL2pp/actions/workflows/ci.yml/badge.svg)](https://github.com/libSDL2pp/libSDL2pp/actions/workflows/ci.yml)
[![Github commits (since latest release)](https://img.shields.io/github/commits-since/libSDL2pp/libSDL2pp/latest.svg)](https://github.com/libSDL2pp/libSDL2pp)

# libSDL2pp

This library provides C++ bindings/wrapper for SDL2 and satellite libraries.

## Synopsis

```cpp
try {
  using namespace SDL2pp;

  // Init SDL; will be automatically deinitialized when the object is destroyed
  SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  // Likewise, init SDL_ttf library
  SDLTTF sdl_ttf;

  // Straightforward wrappers around corresponding SDL2 objects
  // These take full care of proper object destruction and error checking
  Window window("libSDL2pp demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                640, 480, SDL_WINDOW_RESIZABLE);
  Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
  Texture sprite1(renderer, SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_STATIC, 16, 16);
  Texture sprite2(renderer, "sprite.png"); // SDL_image support

  Font font("Vera.ttf", 20); // SDL_ttf font

  // Initialize audio mixer
  Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

  Chunk sound("effect.ogg"); // OGG sound file

  // Create texture from surface containing text rendered by SDL_ttf
  Texture text(renderer, font.RenderText_Solid("Hello, world!",
               SDL_Color{255, 255, 255, 255}));

  unsigned char pixels[16 * 16 * 4];

  // Note proper constructor for Rect
  sprite1.Update(Rect(0, 0, 16, 16), pixels, 16 * 4);

  // Most setter methods are chainable
  renderer.SetLogicalSize(640, 480).SetDrawColor(0, 16, 32).Clear();

  // Also note a safe way to specify null rects and points
  renderer.Copy(sprite1, NullOpt, NullOpt);

  // There are multiple convenient ways to construct e.g. a Rect;
  // Objects provide extensive set of getters
  renderer.Copy(text, NullOpt, Rect(Point(0, 0), text.GetSize()));

  // Copy() is overloaded, providing access to both SDL_RenderCopy and SDL_RenderCopyEx
  renderer.Copy(sprite2, NullOpt, NullOpt, 45.0);

  renderer.Present();

  // Play our sound one time on a first available mixer channel
  mixer.PlayChannel(-1, sound);

  // You can still access wrapped C SDL types
  SDL_Renderer* sdl_renderer = renderer.Get();

  // Of course, C SDL2 API is still perfectly valid
  SDL_Delay(2000);

  // All SDL objects are released at this point or if an error occurs
} catch (SDL2pp::Exception& e) {
  // Exception stores SDL_GetError() result and name of function which failed
  std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
  std::cerr << "  Reason: " << e.GetSDLError() << std::endl;
} catch (std::exception& e) {
  // This also works (e.g. "SDL_Init failed: No available video device")
  std::cerr << e.what() << std::endl;
}
```

There's also more elaborate [tutorial](https://github.com/libSDL2pp/libSDL2pp-tutorial).

## Features

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
* SDL_mixer
  * Library initialization/deinitialization
  * Sound sample handling (Mix_Chunk)
  * Music handling (Mix_Music)
  * Mixer class which encapsulates device handling and all playback functions
* SDL_ttf
  * Library initialization/deinitialization
  * TTF_Font (all functions covered)

each with a subset of methods corresponding to SDL functions working
with specific types of objects and, in some cases, additional convenience
methods. These classes support:

* RAII-style initialization and destruction, automatic resource lifetime
  control (you no longer need to care of manually freeing your stuff)
* Total error checking: exceptions are thrown if any SDL function fails.
  Exception itself allows retrieval of SDL error string (you no longer
  need to manually check return code after each function call)
* Method overloading, default arguments, method chaining allow shorter
  and cleaner code
* Move semantics support, which allow you to store SDL objects
  in containers and pass/return them by value without noticeable overhead

Set of functional extensions above SDL2 is also available:

* RWops adapters for C++ containers and streams
* Optional object to safely handle values which may not be present,
  (for which SDL2 usually uses NULL pointers)
* Number of additional methods and operator support for Point and Rect

## Building

Dependencies:
* [cmake](https://cmake.org/)
* [SDL2](https://libsdl.org/)
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/) (optional)
* [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/) (optional)
* [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (optional)

To build standalone version:

```shell
cmake .
cmake --build .
```

Following variables may be supplied to CMake to affect build:

* `SDL2PP_WITH_IMAGE` - enable SDL_image support (default ON)
* `SDL2PP_WITH_MIXER` - enable SDL_mixer support (default ON)
* `SDL2PP_WITH_TTF` - enable SDL_ttf support (default ON)
* `SDL2PP_WITH_EXAMPLES` - enable building example programs (only for standalone build, default ON)
* `SDL2PP_WITH_TESTS` - enable building tests (only for standalone build, default ON)
* `SDL2PP_STATIC` - build static library instead of shared (only for standalone build, default OFF)
* `SDL2PP_ENABLE_LIVE_TESTS` - enable tests which require X11 and/or audio device to run (only for standalone build, default ON)

## Installation

To install the library system-wide, run:

```shell
cmake .
cmake --build .
cmake --install .
```

You can change installation prefix with CMAKE_INSTALL_PREFIX cmake
variable:

```shell
cmake -DCMAKE_INSTALL_PREFIX=/usr/local .
cmake --build .
cmake --install .
```

SDL2pp installs `pkg-config` file, so it can be used with any build
system that interacts with `pkg-config`, including CMake, meson and
GNU Autotools. It also installs CMake module file, which can be used
from CMake directly:

```cmake
find_package(SDL2pp REQUIRED)

target_link_libraries(mytarget SDL2pp::SDL2pp)
```

## Bundling ##

The library is easy to integrate into other CMake projects
(and as the library has no stable API yet, this way of using it is
still recommended).

Just place the library into dedicated directory in your project
(for example, extlib/libSDL2pp) and add

```cmake
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(extlib/libSDL2pp)
```

into your core CMakeLists.txt. This will act similar to how
`find_package` usually does, and will provide `SDL2pp::SDL2pp`
target for your project. You will then be able it as usual:

```cmake
target_link_libraries(mytarget SDL2pp::SDL2pp)
```

If bundled, libSDL2pp does not build examples and becomes a static
library. See [hoverboard](https://github.com/AMDmi3/hoverboard-sdl/blob/5729f9fb6929f6e8147481f5b21772fc1e35562a/CMakeLists.txt#L34-L40)
project as an example of using both bundled and systemwide SDL2pp.

## Completeness

The library still doesn't cover all aspects of SDL2, and the development
is generally guided by the author's needs and interest without a goal
for covering all SDL2 functions as soon as possible. However, if
you need specific bits which are not yet implemented in the library,
feel free to drop an issue. Patches are of course more than welcome.

It should be noted, however, that I currently do not plan to implement
any wrappers over non object-oriented SDL2 code, as these will not bring
any benefits over using plain C API. E.g. I see no point in implementing
SDL2pp::Delay() as it won't bring any convenience over SDL_Delay().

The same strongly applies to the SDL2 bits which duplicate C++17
standard library, e.g. threads and atomic ops.

## Users

Projects using libSDL2pp:

* [fontbm](https://github.com/vladimirgamalian/fontbm) - Command line font generator, compatible with BMFont
* [hoverboard-sdl](https://github.com/AMDmi3/hoverboard-sdl) - Desktop version of xkcd 1608 "Hoverboard" game
* [neopedersia](https://github.com/vladimirgamalian/neopedersia) - Nexus Wars style game
* [OpenDaed](https://github.com/AMDmi3/opendaed) - Libre reimplementation of The Daedalus Encounter game
* [OpenStrike](https://github.com/AMDmi3/openstrike) - Libre reimplementation of Jungle and Desert Strike games
* [osmview](https://bitbucket.org/ipopov/osmview) - Desktop OpenStreetMap viewer
* [planetonomy](https://github.com/AMDmi3/planetonomy) - Old-school platformer/exploration game with CGA graphics

## WWW

* [GitHub page](https://github.com/libSDL2pp/libSDL2pp)
* [Online documentation](https://sdl2pp.amdmi3.ru/)

## Author

* [Dmitry Marakasov](https://github.com/AMDmi3) <amdmi3@amdmi3.ru>

## Contributors

* [Aargonian](https://github.com/Aargonian)
* [Carl Schwope](https://github.com/Lowest0ne)
* [Carsten Elton Sorensen](https://github.com/csoren)
* [Ilya Popov](https://github.com/ilyapopov)
* [kumar8600](https://github.com/kumar8600)
* [ooxi](https://github.com/ooxi)
* [Vladimir Gamalian](https://github.com/vladimirgamalian)
* [Vraiment](https://github.com/Vraiment)

## License

libSDL2pp comes under zlib license, the same license as SDL2. See COPYING.txt.
